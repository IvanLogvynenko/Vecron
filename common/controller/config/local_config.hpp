#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace config {

class LocalConfiguration {
private:
    std::string _configPath;

    std::optional<std::string> _build, _run, _init, _initBuild, _initRun;

    nlohmann::json _data;

public:
    explicit LocalConfiguration(std::string);
    ~LocalConfiguration() = default;

    inline const std::string &getConfigPath() const noexcept { return _configPath; }
    const std::optional<std::string> &getBuildCMD() noexcept;
};

} // namespace config
