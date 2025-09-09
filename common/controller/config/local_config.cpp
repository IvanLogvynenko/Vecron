#include "local_config.hpp"

#include <filesystem>
#include <fstream>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <print>
#include <utility>

namespace config {

LocalConfiguration::LocalConfiguration(std::string configPath) : _configPath(std::move(configPath)) {
    std::println("main path: {}", _configPath + "main.json");
    if (std::filesystem::exists(_configPath + "main.json")) {
        std::ifstream mainFile{_configPath + "main.json"};
        nlohmann::json data = nlohmann::json::parse(mainFile);

        // hardcoding needed values
        if (data.contains("build"))
            this->_build = data["build"];
        else
            this->_build = std::nullopt;

        if (data.contains("run"))
            this->_run = data["run"];
        else
            this->_run = std::nullopt;

        if (data.contains("init"))
            this->_init = data["init"];
        else
            this->_init = std::nullopt;
		
        if (data.contains("initBuild"))
            this->_initBuild = data["initBuild"];
        else
            this->_initBuild = std::nullopt;

        if (data.contains("initRun"))
            this->_initRun = data["initRun"];
        else
            this->_initRun = std::nullopt;
    }
    // std::println("Getting local configuration from {}", _configPath);
}

} // namespace config
