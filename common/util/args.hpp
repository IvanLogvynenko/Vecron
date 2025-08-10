#pragma once

#include <map>
#include <string>
#include <vector>

namespace util {

std::pair<std::map<std::string, std::string>, std::vector<std::string>>
parse_args(const std::vector<std::string> &);

} // namespace util
