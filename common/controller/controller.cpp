#include "controller.hpp"
#include "command/command.hpp"
#include "config/global_config.hpp"
#include "controller/config/local_config.hpp"
#include "controller/config/invalid_config_exception.hpp"
#include "util/args.hpp"
#include "util/home.hpp"
#include <filesystem>
#include <functional>
#include <iostream>
#include <memory>
#include <print>
#include <string>

namespace controller {

Controller::Controller(const std::vector<std::string> &args) {
    auto [data, rest] = util::parse_args(args);
    // if data has no configPath then it will be "" and getGlobalConfigPath has a fallback for such case
    // INFO Loading globalConfig, if none throwing error
    auto globalConfigPath = config::getGlobalConfigPath(data["configPath"]);
    try {
        this->_globalConfig = std::make_unique<config::GlobalConfiguration>(globalConfigPath);
    } catch (config::GlobalConfigNotFound) {
        std::string config = util::home() + ".config/vecron", share = util::home() + ".local/share/vecron";

        if (data["configPath"] != "") {
            std::println("Config was not found at {}\nPlease provide valid path, or use config at \n{}\nor\n{}",
                         data["configPath"],
                         config,
                         share);
        } else {
            std::println("No config found at expected paths: \n{}\n{}\nPlease create one!", config, share);
        }
        exit(1);
    }

    // INFO Global config loaded, lodaing variables
    std::string targetPath = data["targetPath"];
    if (targetPath == "") targetPath = std::filesystem::current_path();
    if (!targetPath.ends_with("/")) targetPath += "/";
    this->_targetPath = targetPath;

    this->_database["targetPath"] = targetPath;
	//Loading it just to be able to use it
    this->_database["projectPath"] = targetPath;
    this->_database["projectDir"] = targetPath;

    // INFO Probing for vecron dir
    if (std::filesystem::exists(targetPath + ".vecron")) {
		// std::println("found .vecron!");
		try {
			this->_localConfig = std::make_unique<config::LocalConfiguration>(targetPath + ".vecron/");
		} catch (config::InvalidConfig e) {
			std::println("Caught error while reading local config:\n", e.what());
		}

	}

    this->_inputQueue.push_range(rest);
}

int Controller::start() {
    std::unique_ptr<command::Command> selected = this->prompt(std::move(this->_commands));

    std::unique_ptr<command::Command> command = std::move(selected);
    return command->exec(*this);
    // might get handy later
    // this->_commands.clear();
    // for (auto &tmp : command->getCommands()) {
    //     this->_commands.push_back(std::move(tmp));
    // }
}

std::string Controller::textPrompt(const std::string &msg,
                                   const std::function<bool(const std::string &)> &valid,
                                   const std::string &prompt) {
    std::string userInput = "";
    bool input_taken = false;
    if (!_inputQueue.empty()) {
        input_taken = true;
        userInput = _inputQueue.front();
        _inputQueue.pop();
    }

    while (!input_taken || !valid(userInput)) {
        input_taken = true;
        std::println("{}", msg);
        std::print("{}", prompt);
        std::getline(std::cin, userInput);
    }
    return userInput;
}

} // namespace controller
