#include "controller.hpp"
#include "command/command.hpp"
#include "config/global_config.hpp"
#include "fzf/fzf_prompt.hpp"
#include "util/args.hpp"
#include "util/home.hpp"
#include <filesystem>
#include <memory>
#include <print>

namespace controller {

Controller::Controller(const std::vector<std::string> &args) {
    auto [data, rest] = util::parse_args(args);
    // if data has no configPath then it will be "" and getGlobalConfigPath has a fallback for such case
    auto globalConfigPath = config::getGlobalConfigPath(data["configPath"]);
    try {
        this->_globalConfig =
            std::make_unique<config::GlobalConfiguration>(globalConfigPath);
    } catch (config::GlobalConfigNotFound) {
        std::string config = util::home() + ".config/vecron",
                    share = util::home() + ".local/share/vecron";
        if (data["configPath"] != "") {
            std::println("Config was not found at {}\nPlease provide valid "
                         "path, or use config at "
                         "\n{}\nor\n{}",
                         data["configPath"],
                         config,
                         share);
            exit(1);
        }
        std::println("No config found at expected paths: \n{}\n{}\nPlease "
                     "create one!",
                     config,
                     share);
    }

    std::string targetPath = data["targetPath"];
    if (targetPath == "") targetPath = std::filesystem::current_path();

    this->_inputQueue.push_range(rest);
}

int Controller::start() {
    std::vector<std::unique_ptr<command::Command>> selected =
        fzf::prompt(std::move(this->_commands));

    if (selected.size() != 1) {
        std::println("Multiple commands selected... exiting");
        exit(1);
    }

    std::unique_ptr<command::Command> command = std::move(selected[0]);
	return command->exec(this);
	// might get handy later
    // this->_commands.clear();
    // for (auto &tmp : command->getCommands()) {
    //     this->_commands.push_back(std::move(tmp));
    // }

}

} // namespace controller
