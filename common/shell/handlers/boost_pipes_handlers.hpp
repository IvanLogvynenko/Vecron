#pragma once

#include <boost/asio.hpp>

namespace common::shell::handlers {

class OutPipeHandler {
public:
    using ioHandler = boost::asio::readable_pipe;

protected:
    ioHandler _pipe;

public:
    OutPipeHandler(boost::asio::io_context &ctx) : _pipe{ctx} {}
    constexpr ioHandler &get() { return this->_pipe; }
};

class ErrPipeHandler : public OutPipeHandler {
public:
    ErrPipeHandler(boost::asio::io_context &ctx) : OutPipeHandler{ctx} {}
};

class InPipeHandler {
public:
    using ioHandler = boost::asio::writable_pipe;

protected:
    ioHandler _pipe;

public:
    InPipeHandler(boost::asio::io_context &ctx) : _pipe{ctx} {}
    constexpr ioHandler &get() { return _pipe; }
};

} // namespace common::shell::handlers
