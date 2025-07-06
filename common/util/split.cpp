#include "split.hpp"
#include <sstream>
#include <string>
#include <vector>

namespace common::util {

std::vector<std::string> split(const std::string& input, char delimiter) {
    std::vector<std::string> result = {};
    std::stringstream ss(input);
    std::string line;
    while (std::getline(ss, line, delimiter)) result.push_back(line);
    return result;
}

} // namespace common::util
