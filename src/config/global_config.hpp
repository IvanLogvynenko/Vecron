#pragma once

#include "fstream"
#include "nlohmann/json.hpp"
#include <string>

namespace config {

class GlobalConfiguration {
    explicit GlobalConfiguration(const std::string &path) {
        std::ifstream f(path);
        nlohmann::json data = nlohmann::json::parse(f);
    }
};

} // namespace config
