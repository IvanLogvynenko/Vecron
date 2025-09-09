#pragma once

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>

namespace config {

class LocalConfiguration {
private:
    std::string _configPath;

	std::optional <std::string> _build, _run, _init, _initBuild, _initRun;

public:
    explicit LocalConfiguration(std::string);
    ~LocalConfiguration() = default;

    inline const std::string &getConfigPath() const noexcept { return _configPath; }
};

} // namespace config
