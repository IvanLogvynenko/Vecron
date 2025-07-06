#pragma once

#include <exception>
#include <initializer_list>
#include <sstream>
#include <vector>

namespace common::util {

class ProcessException : public std::exception {
private:
	unsigned _code;
	std::string _message;
public:
	ProcessException(std::string, unsigned);
	const char* what() const noexcept override;
};

class Process {
private:
    std::stringstream in;
    std::stringstream out;
    std::stringstream err;

    std::string _command;
    std::vector<std::string> _args;

public:
    explicit Process(const std::string& command);
    Process(std::string command, std::initializer_list<std::string> args);
    Process(std::string command, std::vector<std::string> args);

    Process(const Process &) = delete;
    Process &operator=(const Process &) = delete;

    Process(Process &&) noexcept;
    Process &operator=(Process &&) noexcept;

    /* *
	 * runs the program with given args and returns output, throws process::runtime_error if err is not empty
	 */
    std::string run();

    /**
	 * Accepts data as: <input data> | <program name> <arguments>
	 * */
    static std::string run(const std::string &command);

    template <typename T> Process &operator<<(const T &value) {
        in << value;
        return *this;
    }
};

} // namespace common::util
