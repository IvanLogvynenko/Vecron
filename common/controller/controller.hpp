#pragma once

#include "command/command.hpp"
#include "config/global_config.hpp"
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <vector>

namespace controller {

/**
 * @class Controller
 * @brief Controller is deigned to manage everything vecron needs to run.
 *
 * Controller manages configs, global and local config, LuaJIT and user module loading.
 *
 * TODO  Add local config
 * TODO: Add module loading + storing
 * TODO  Add LuaJIT
 */
class Controller {
private:
    std::vector<std::unique_ptr<command::Command>> _commands;

	std::queue<std::string> _inputQueue;

    std::map<std::string, std::string> _database;

    std::unique_ptr<config::GlobalConfiguration> _globalConfig;
    std::string _targetPath;

public:
    /**
	 * @brief Parses args (program name preexcluded) and loades data when needed
	 *
	 * @param args Arguments passed to program during start
	 */
    Controller(const std::vector<std::string> &args);

    Controller(const Controller &) = delete;
    Controller(Controller &&) = delete;
    Controller &operator=(const Controller &) = delete;
    Controller &operator=(Controller &&) = delete;

    int start();

    inline void addCommand(std::unique_ptr<command::Command> command) {
        this->_commands.push_back(std::move(command));
    }

    inline const config::GlobalConfiguration &getGlobalConfig() const noexcept {
        return *_globalConfig;
    }
    inline const std::string &getTargetPath() const noexcept {
        return _targetPath;
    }
};

} // namespace controller
