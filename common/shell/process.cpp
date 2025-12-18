#include "process.hpp"

#include <boost/asio.hpp>
#include <boost/process/process.hpp>

#include <boost/process.hpp>

namespace common::shell {

ProcessException::ProcessException(std::string message, unsigned code) : _code(code), _message(std::move(message)) {
    if (_code == 0) { throw std::runtime_error("Well, guest what? 0 means success man"); }
}

const char *ProcessException::what() const noexcept { return this->_message.c_str(); }

// Process::Process(std::string command) {
//     boost::asio::io_context ctx = {};
//     auto pipe_stdout = std::make_unique<boost::asio::readable_pipe>(ctx);
//     std::println("Start");
//     boost::process::process proc(ctx,
//                                  "echo",
//                                  {"$DATA"},
//                                  boost::process::process_stdio{.in = nullptr, .out = *pipe_stdout, .err = nullptr},
//                                  boost::process::process_environment(my_env));
//     std::array<char, 1024> buf;
//     pipe_stdout->read_some(boost::asio::buffer(buf));
//     std::print("{}", buf.data());
//     std::println("End");
// 	return buf.data();
// }

// template <handlers::Handler InputHandler, handlers::Handler ErrorHandler, handlers::Handler OutputHandler>
Process::Process(boost::asio::io_context &ctx,
                 const std::string &shellPath,
                 const std::string &command,
                 const std::map<std::string, std::string> &environment)
    : _process{ctx,
               shellPath,
               {"-c", command},
               boost::process::process_stdio{
                   .in = InputHandler.get(), .out = OutputHandler.get(), .err = ErrorHandler.get()},
               boost::process::process_environment(environment)} {}

// Process::Process(Process &&other) noexcept {}
//
// Process &Process::operator=(Process &&other) noexcept {
//     if (this != &other) {
//         this->_command = std::move(other._command);
//     }
//     return *this;
// }

template <handlers::Handler InputHandler, handlers::Handler ErrorHandler, handlers::Handler OutputHandler>
int Process::run() {
    while (_process.running());
    return _process.exit_code();
}

// int Process::run(const std::string &command) {
//     Process p(command);
//     return p.run();
// }

} // namespace common::shell
