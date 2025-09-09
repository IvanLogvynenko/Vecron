#include "cli/common.hpp"
#include "command/build.hpp"
#include "command/debug.hpp"
#include "command/new_command.hpp"
#include "command/preprocess.hpp"
#include "controller/controller.hpp"

#include <memory>
#include <vector>

int main(int argc, char **argv) {
    // Load args in std::vector, omit program name and pass them to controller
    std::vector<std::string> args_str = {};
    argc -= 1;
    args_str.reserve(static_cast<size_t>(argc));
    for (int i = 1; i < argc + 1; i++) { args_str.emplace_back(*(argv + i)); }

    controller::Controller controller{args_str};
    cli::clear();
    cli::printLogo();

    controller.addCommand(std::make_unique<command::Debug>());
    controller.addCommand(std::make_unique<command::NewCommand>());
    controller.addCommand(std::make_unique<command::Build>());
    controller.addCommand(std::make_unique<command::Preprocess>());

    // int exit_code = 
		return controller.start();
    // return exit_code;
}
