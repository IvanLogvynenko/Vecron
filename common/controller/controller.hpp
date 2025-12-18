#pragma once

#include "command/command.hpp"
#include "config/global_config.hpp"
#include "controller/config/local_config.hpp"
#include "fzf/fzf_modes.hpp"
#include "fzf/fzf_prompt.hpp"
#include "module/module.hpp"
#include "shell/shell.hpp"
#include <boost/asio/io_context.hpp>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <regex>

namespace controller {

/**
 * @class Controller
 * @brief Controller is deigned to manage everything vecron needs to run.
 *
 * Controller manages configs, global and local config, LuaJIT and user module loading.
 * Controller rarely does something itself and relies on commands requesting data
 *
 * TODO  Add local config
 * TODO: Add module loading + storing
 * TODO  Add LuaJIT
 */
class Controller {
private:
	std::regex pattern{R"(\{\{(\w+)\}\})"};

    std::vector<std::unique_ptr<command::Command>> _commands = {};

    std::queue<std::string> _inputQueue = {};

    std::mutex _db_lock;
    std::map<std::string, std::string> _database;

    std::unique_ptr<config::GlobalConfiguration> _globalConfig;
    std::unique_ptr<config::LocalConfiguration> _localConfig;
    std::string _targetPath = "";

    std::optional<module::Module> _buildProvider;

	//boost operationals
	boost::asio::io_context _boost_ctx;

	common::shell::Shell _shell;

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

    ~Controller() = default;

    int start();

    template <typename T> T prompt(std::vector<T> &&data) {
        std::vector<T> selected = {};
        if (!this->_inputQueue.empty()) {
            selected = fzf::prompt(std::move(data), {fzf::mode::pattern(_inputQueue.front())});
            _inputQueue.pop();
        } else
            selected = fzf::prompt(std::move(data));

        if (selected.size() == 1) {
            return std::move(selected[0]);
        } else {
            throw std::runtime_error("Multiple targets selected");
        }
    }

    std::string textPrompt(
        const std::string & = "",
        const std::function<bool(const std::string &)> & = [](const std::string &input) { return input != ""; },
        const std::string & = ">>> ");

    inline void addCommand(std::unique_ptr<command::Command> command) { this->_commands.push_back(std::move(command)); }

    inline std::optional<std::string> operator[](const std::string &key) { return this->getVariable(key); }
    inline std::optional<std::string> getVariable(const std::string &key) {
        if (_database.contains(key))
            return _database[key];
        else
            return std::nullopt;
    }

    void addVariableValue(const std::string &key, std::string value) { _database[key] = std::move(value); }
    inline const std::map<std::string, std::string> &getAllVariables() { return this->_database; }

    // INFO: Use safe version if you don't want to lock and unlock manually
    // best suits for single line preprocessing
    // If you have more data to be processed and you see that you will be (un)locking it often
    // then you should lock it one, process stuff and unlock
    void lockDataBase();
    void unlockDataBase();
	std::pair<std::string, std::set<std::string>> preprocessString(const std::string &);
    std::pair<std::string, std::set<std::string>> preprocessStringSafe(const std::string &);
	std::set<std::string> preprocessStringstream(std::istream &in, std::ostream &out);
	std::set<std::string> preprocessStringstreamSafe(std::istream &in, std::ostream &out);

    inline const config::GlobalConfiguration &getGlobalConfig() const noexcept { return *_globalConfig; }
    inline const config::LocalConfiguration &getLocalConfig() const noexcept { return *_localConfig; }
    inline const std::string &getTargetPath() const noexcept { return _targetPath; }

	std::shared_ptr<common::shell::Shell> getShell() const;
};

} // namespace controller
