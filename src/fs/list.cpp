#include "list.hpp"
#include <filesystem>
#include <ranges>
#include <stdexcept>

namespace fs {

std::vector<std::string> listFiles(const std::string &path) {
    if (!std::filesystem::is_directory(path)) {
        throw std::runtime_error(path + " is a file, not a directory");
    }

    return std::ranges::to<std::vector<std::string>>(
        std::filesystem::directory_iterator(path) |
        std::views::filter(
            [](const auto &entry) { return !entry.is_directory(); }) |
        std::views::transform([](const auto &entry) {
            return entry.path().filename().string();
        }));
}

std::vector<std::string> listDirectories(const std::string &path) {
    if (!std::filesystem::is_directory(path)) {
        throw std::runtime_error(path + " is a file, not a directory");
    }

    return std::ranges::to<std::vector<std::string>>(
        std::filesystem::directory_iterator(path) |
        std::views::filter(
            [](const auto &entry) { return entry.is_directory(); }) |
        std::views::transform([](const auto &entry) {
            return entry.path().filename().string();
        }));
}

std::vector<std::string> treeDirectory(const std::string& path) {
    if (!std::filesystem::is_directory(path)) {
        throw std::runtime_error(path + " is a file, not a directory");
    }

	return {};
}


} // namespace fs
