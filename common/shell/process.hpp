#pragma once

#include "shell/handler.hpp"
#include <boost/asio/readable_pipe.hpp>
#include <boost/asio/writable_pipe.hpp>
#include <boost/process.hpp>
#include <exception>
#include <map>

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
    InputHandler _in;
    ErrorHandler _err;
    OutputHandler _out;
    boost::process::process _process;

    friend class Shell;

public:
    Process(boost::asio::io_context &ctx,
            const std::string &shellPath,
            const std::string &command,
            const std::map<std::string, std::string> &environment);

    // explicit Process(const std::string &command);
    ~Process() = default;

    // Process(const Process &) = delete;
    // Process &operator=(const Process &) = delete;
    //
    // Process(Process &&) noexcept;
    // Process &operator=(Process &&) noexcept;

    /* *
	 * runs the program with given args and returns exit_code
	 */
    int run();

    /**
	 * Accepts and runs command
	 * */
    // static int run(const std::string &command);

    // template <typename T> Process &operator<<(const T &value) {
    //     in << value;
    //     return *this;
    // }
};

} // namespace common::shell
