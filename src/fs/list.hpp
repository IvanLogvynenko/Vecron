#pragma once

#include <string>
#include <vector>

namespace fs {

std::vector<std::string> listFiles(const std::string& path);
std::vector<std::string> listDirectories(const std::string& path);
std::vector<std::string> treeDirectory(const std::string& path);

} // namespace fs
