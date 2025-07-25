#pragma once

#include <string>
#include <vector>

namespace fs {
/*
 * Lists files inside a directory
 */
std::vector<std::string> listFiles(const std::string& path);

/*
 *  Lists directories in a directory
 */
std::vector<std::string> listDirectories(const std::string& path);

/*
 * Lists files in directory recursively
 */
std::vector<std::string> treeDirectory(const std::string& path);

} // namespace fs
