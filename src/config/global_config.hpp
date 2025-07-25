#pragma once

#include "fstream"
#include "nlohmann/json.hpp"
#include <exception>
#include <fstream>
#include <string>

namespace config {

std::optional<std::string> getGlobalConfigPath();

class GlobalConfigNotFound : std::exception {};

class GlobalConfiguration {
private:
    std::string targetPath, configPath;

public:
    explicit GlobalConfiguration() {
        auto tmp = getGlobalConfigPath();
        if (!tmp.has_value()) throw GlobalConfigNotFound();
		const std::string& path = tmp.value();

		std::ifstream configFile(path);
		nlohmann::json data = nlohmann::json::parse(configFile);
    }
};

} // namespace config
