#pragma once

#include <exception>
#include <optional>
#include <string>

namespace config {

/**
 * @brief Searches for global configuration
 *
 * @warning Doesn't check if found config is valid. 
 *
 * @param path path where to search for config. Will try to add /config.json, so you can pass just a dir where it can be.
 *
 * @return Either path to directory where config is stored, or std::nullopt
 * @hint If path/to/dir/config.json is passed path/to/dir/ will be returned
 */
std::optional<std::string> getGlobalConfigPath(std::string = "") noexcept;

class GlobalConfigNotFound : public std::exception {};
class GlobalConfigInvalid : public std::exception {};

class GlobalConfiguration {
private:
    std::string _templatePath = "";

public:
    explicit GlobalConfiguration(const std::string & = "");
    explicit GlobalConfiguration(std::optional<std::string>);

    GlobalConfiguration(const GlobalConfiguration &) = delete;
    GlobalConfiguration(GlobalConfiguration &&) = delete;
    GlobalConfiguration &operator=(const GlobalConfiguration &) = delete;
    GlobalConfiguration &operator=(GlobalConfiguration &&) = delete;

    inline const std::string &getTemplatePath() const noexcept { return _templatePath; }
};

} // namespace config
