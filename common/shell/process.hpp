#pragma once

#include "shell/handlers/handler.hpp"
#include <boost/asio/io_context.hpp>
#include <boost/asio/readable_pipe.hpp>
#include <boost/asio/writable_pipe.hpp>
#include <boost/process.hpp>
#include <cassert>
#include <concepts>
#include <exception>
#include <map>
#include <memory>

namespace common::shell {

class ProcessException : public std::exception {
private:
    unsigned _code;
    std::string _message;

public:
    ProcessException(std::string, unsigned);
    const char *what() const noexcept override;
};

template <handlers::Handler InputHandler, handlers::Handler ErrorHandler, handlers::Handler OutputHandler>
class Process {
private:
    std::unique_ptr<InputHandler> _in;
    std::unique_ptr<ErrorHandler> _err;
    std::unique_ptr<OutputHandler> _out;
    std::unique_ptr<boost::process::process> _process;

    friend class Shell;
    template <class Handler> std::unique_ptr<Handler> createHandler(boost::asio::io_context &ctx) {
        if constexpr (std::constructible_from<Handler>) {
            return std::make_unique<Handler>();
        } else if constexpr (std::constructible_from<Handler, boost::asio::io_context &>) {
            return std::make_unique<Handler>(ctx);
        } else {
            static_assert(
                false, "Only stdio and boost pipes are supported, use (or override) one of the given implementations");
        }
    }

public:
    Process(boost::asio::io_context &ctx,
            const std::string &shellPath,
            const std::string &command,
            const std::map<std::string, std::string> &environment) {
        _in = this->createHandler<InputHandler>(ctx);
        _err = this->createHandler<ErrorHandler>(ctx);
        _out = this->createHandler<OutputHandler>(ctx);
        _process = std::make_unique<boost::process::process>(
            ctx,
            shellPath,
            std::vector<std::string>{"-c", command},
            boost::process::process_stdio{.in = _in->get(), .out = _out->get(), .err = _err->get()},
            boost::process::process_environment(environment));
    }

    ~Process() = default;

    Process(const Process &) = delete;
    Process &operator=(const Process &) = delete;

    Process(Process &&) noexcept = default;
    Process &operator=(Process &&) = default;

    /* *
	 * runs the program with given args and returns exit_code
	 */
    int run() {
        while (_process->running());
        return _process->exit_code();
    }

    InputHandler &getIn() { return *_in; }
    ErrorHandler &getErr() { return *_err; }
    OutputHandler &getOut() { return *_out; }
};

} // namespace common::shell
