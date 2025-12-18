#include "shell.hpp"

namespace common::shell {

Shell::Shell(boost::asio::io_context &ctx, std::map<std::string, std::string> environment, std::string shellPath)
    : _ctx(ctx), _environment(std::move(environment)), _shellPath(std::move(shellPath)) {}

template <handlers::Handler InputHandler, handlers::Handler ErrorHandler, handlers::Handler OutputHandler>
std::unique_ptr<common::shell::Process<InputHandler, ErrorHandler, OutputHandler>>
Shell::execute(const std::string &command) {
    return std::make_unique<common::shell::Process<InputHandler, ErrorHandler, OutputHandler>>(
        this->_ctx, this->_shellPath, command, this->_environment);
}

} // namespace common::shell
