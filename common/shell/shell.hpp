#pragma once

#include "shell/handlers/stdio_handlers.hpp"
#include "shell/process.hpp"

// INFO: General idea is that Shell will create a Process instance, that user can use to interact with and info that is being outputted in the shell

namespace common::shell {

class Shell {
private:
    boost::asio::io_context &_ctx;
    std::map<std::string, std::string> _environment;
    std::string _shellPath;

public:
    Shell(boost::asio::io_context &, std::map<std::string, std::string> _environment = {}, std::string = "/bin/sh");

    ~Shell() = default;

    /*
	* @brief creates a process and starts it immediatelly. 
	*/
    template <handlers::Handler InputHandler = handlers::StdinHandler,
              handlers::Handler ErrorHandler = handlers::StderrHandler,
              handlers::Handler OutputHandler = handlers::StdoutHandler>
    std::unique_ptr<Process<InputHandler, ErrorHandler, OutputHandler>> execute(const std::string &command) {
        return std::make_unique<common::shell::Process<InputHandler, ErrorHandler, OutputHandler>>(
            this->_ctx, this->_shellPath, command, this->_environment);
    }

    void clear() {
        if (!_environment.contains("TERM")) {
            throw common::shell::ProcessException("Unknown terminal, no info how to clear", 1);
        }
        this->execute("clear");
    }

    template <handlers::Handler InputHandler = handlers::StdinHandler,
              handlers::Handler ErrorHandler = handlers::StderrHandler,
              handlers::Handler OutputHandler = handlers::StdoutHandler>
    static std::unique_ptr<Process<InputHandler, ErrorHandler, OutputHandler>>
    execute(const std::string &command,
			boost::asio::io_context& ctx,
            std::map<std::string, std::string> environment = {},
            std::string shellPath = "/bin/sh") {
        return std::make_unique<common::shell::Process<InputHandler, ErrorHandler, OutputHandler>>(
            ctx, shellPath, command, environment);
    }
};

} // namespace common::shell
