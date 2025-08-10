#include "global_config.hpp"
#include "util/home.hpp"
#include <filesystem>
#include <optional>

namespace config {

std::optional<std::string> getGlobalConfigPath(std::string path) noexcept {
    // searching for config in given path
    if (path != "") {
        if (std::filesystem::is_directory(path)) {
            // if directory -> searching for path/to/dir + /config.json or path/to/dir/ + config.json
            if (std::filesystem::exists(path + "config.json"))
                return path;
            else if (std::filesystem::exists(path + "/config.json"))
                return path + '/';
        } else if (std::filesystem::exists(path) &&
                   path.ends_with("/config.json"))
            return path.substr(0,
                               path.length() - 11); // config.json is 11 chars
        return std::nullopt;
    }

    // if no path was passed, then searching paths where configurator whould have stored config
    std::string home = util::home();
    if (std::filesystem::exists(home + ".config/vecron/config.json")) {
        return home + ".config/vecron/";
    }
    if (std::filesystem::exists(home + ".local/share/vecron/config.json")) {
        return home + ".config/vecron/";
    }
    return std::nullopt;
}

GlobalConfiguration::GlobalConfiguration(const std::string &path)
    : _templatePath(path + "templates/") {
}

GlobalConfiguration::GlobalConfiguration(std::optional<std::string> opt_path)
    : config::GlobalConfiguration(opt_path ? opt_path.value() :
                                             throw GlobalConfigNotFound{}) {}

} // namespace config
