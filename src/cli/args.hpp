#pragma once

#include <map>
#include <string>
#include <vector>
namespace cli {

std::pair<std::map<std::string, std::string>, std::vector<std::string>>
    parse_args(std::vector<std::string>&);

} // namespace cli
