#include "shell.hpp"

namespace common::shell {

Shell::Shell(boost::asio::io_context &ctx, std::map<std::string, std::string> environment, std::string shellPath)
    : _ctx(ctx), _environment(std::move(environment)), _shellPath(std::move(shellPath)) {}

} // namespace common::shell
