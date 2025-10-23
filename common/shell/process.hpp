#pragma once

#include <exception>
#include <sstream>

namespace common::shell {

class ProcessException : public std::exception {
private:
    unsigned _code;
    std::string _message;

public:
    ProcessException(std::string, unsigned);
    const char *what() const noexcept override;
};

class Process {
private:
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;

    std::string _command;

public:
    explicit Process(std::string command) : _command(std::move(command)) {}

    Process(const Process &) = delete;
    Process &operator=(const Process &) = delete;

    Process(Process &&) noexcept;
    Process &operator=(Process &&) noexcept;

    /* *
	 * runs the program with given args and returns output, throws process::runtime_error if err is not empty
	 */
    std::string run();

    /**
	 * Accepts and runs command
	 * */
    static std::string run(const std::string &command);

    template <typename T> Process &operator<<(const T &value) {
        in << value;
        return *this;
    }
};

} // namespace common::shell
