#pragma once

#include "shell/handlersImpl.hpp"
#include "shell/process.hpp"

// INFO: General idea is that Shell will create a Process instance, that user can use to interact with what is being outputted in the shell

namespace common::shell {

class Shell {
private:
    boost::asio::io_context &_ctx;
    std::map<std::string, std::string> _environment;
    std::string _shellPath;

public:
    Shell(boost::asio::io_context &, std::map<std::string, std::string> _environment = {}, std::string = "/bin/sh");

    ~Shell() = default;

    //   /*
    // * @brief creates a process that caller will start later. Use if you want to configure how process will be executed before starting it
    // * */
    //   std::unique_ptr<Process> create(const std::string &);
    /*
	* @brief creates a process and starts it immediatelly. 
	*/
    template <handlers::Handler InputHandler = handlers::StdinHandler,
              handlers::Handler ErrorHandler = handlers::StderrHandler,
              handlers::Handler OutputHandler = handlers::StdoutHandler>
    std::unique_ptr<Process<InputHandler, ErrorHandler, OutputHandler>> execute(const std::string &);
};

} // namespace common::shell
