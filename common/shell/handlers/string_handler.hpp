#pragma once

#include "shell/handlers/boost_pipes_handlers.hpp"
#include <boost/asio.hpp>
#include <boost/process.hpp>
#include <boost/process/v2/detail/config.hpp>
#include <stdexcept>
#include <string>

namespace common::shell::handlers {

constexpr const char DELIMITER = '\n';

class PipeReader : public OutPipeHandler {
protected:
    bool _eof;

private:
    boost::asio::streambuf _buf;

public:
    PipeReader(boost::asio::io_context &ctx) : OutPipeHandler(ctx), _eof(false), _buf{} {}

    // TODO: find a better way to read data from streambuf to string as istream is slow
    std::string getLine() {
        if (_eof) { throw std::runtime_error("OutStringHandler::getLine() called after EOF"); }

        boost::process::error_code ec;

        boost::asio::read_until(_pipe, _buf, DELIMITER, ec);

        if (ec) {
            if (ec == boost::asio::error::eof) {
                _eof = true;

                if (_buf.size() > 0) {
                    std::istream is(&_buf);
                    std::string line;
                    std::getline(is, line);
                    return line;
                }
                return "";
            } else {
                throw std::runtime_error("Read error: " + ec.message());
            }
        }

        std::istream is(&_buf);
        std::string line;
        std::getline(is, line);

        return line;
    }

    inline bool eof() const { return _eof; }
    operator bool() const { return _eof; }
};

// INFO: dumb aliasing
// TODO: find a better solution
// 1st idea: just readerwriter without specification
class OutStringHandler : public PipeReader {};
class ErrStringHandler : public PipeReader {};

class InStringHandler : public InPipeHandler {
public:
    InStringHandler(boost::asio::io_context &ctx) : InPipeHandler{ctx} {}
    void write(const std::string &line) {
        boost::system::error_code ec;
        auto buf = boost::asio::buffer(line);
        size_t n = this->_pipe.write_some(buf, ec);
        if (n != line.size()) {
            throw std::runtime_error("Failed to write " + std::to_string(line.size()) + "/" + std::to_string(n) +
                                     "\nError: " + ec.what());
        }
    }

    // This method has to be called after all input is written, as the next process will be waiting for eof to execute
    void done() { this->_pipe.close(); }
};

} // namespace common::shell::handlers
