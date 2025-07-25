#include "global_config.hpp"
#include "fs/home.hpp"
#include <filesystem>

namespace config {

std::optional<std::string> getGlobalConfigPath() {
    std::string home = fs::home();
    if (std::filesystem::exists(home + "/.config/vecron/config.json")) {
        return home + "/config/.vecron";
    }
    if (std::filesystem::exists(home + "/.local/share/vecron/config.json")) {
        return home + "/config/.vecron";
    }
    return std::nullopt;
}

} // namespace config
