#include "cli/common.hpp"
#include "command/debug.hpp"
#include "command/new_command.hpp"
#include "fzf/fzf_prompt.hpp"

#include <iostream>
#include <memory>
#include <vector>

#include "command/command.hpp"

int main(int, char **) {
    // if (argv) {
    //     std::vector<std::string> args_str = {};
    //     args_str.reserve(static_cast<size_t>(argv));
    //     for (int i = 0; i < argv; i++) { args_str.emplace_back(*(argc + i)); }
    //     auto [args, rest] = cli::parse_args(args_str);
    // }
	cli::clear();
    cli::printLogo();
    std::vector<std::unique_ptr<command::Command>> options = {};
    options.push_back(std::make_unique<command::NewCommand>());
    options.push_back(std::make_unique<command::Debug>());

    std::vector<std::unique_ptr<command::Command>> selections =
        fzf::prompt(std::move(options));
    if (selections.size() != 1) {
        std::cerr << "Multiple commands selected, action not "
                     "permitted\nExitting...\n";
        return 1;
    }
    selections[0]->execute();

    return 0;
}
