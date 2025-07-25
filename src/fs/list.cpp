#include "list.hpp"
#include <filesystem>
#include <ranges>
#include <stack>
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

	std::vector<std::string> result = {};

	std::stack<std::string> unvisited_directories = {};
	unvisited_directories.push(path);
	
	while (!unvisited_directories.empty()) {
		std::string directory = unvisited_directories.top();
		unvisited_directories.pop();
		for (const auto& entry : std::filesystem::directory_iterator(directory)) {
			if (entry.is_directory()) 
				unvisited_directories.push(entry.path());
			else 
				result.push_back(entry.path());
		}
		
	}


	return result;
}


} // namespace fs
