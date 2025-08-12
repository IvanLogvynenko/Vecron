#include "new_command.hpp"
#include "controller/controller.hpp"
#include "fs/list.hpp"
#include <filesystem>
#include <fstream>
#include <mutex>
#include <print>
#include <regex>
#include <set>
#include <stdexcept>
#include <string>
#include <thread>

int command::NewCommand::exec(controller::Controller &controller) noexcept {
    std::string templatesPath = controller.getGlobalConfig().getTemplatePath();
	std::string templateName = controller.prompt(fs::listDirectories(templatesPath));
    std::string selectedTemplatePath = templatesPath + templateName + "/";
    std::vector<std::thread> fileProcessors{};

    std::string projectName = controller.textPrompt("Enter project name", [](const std::string &input) {
        std::regex validator(R"(^[a-zA-Z0-9_-]+$)");
        if (std::regex_match(input.c_str(), validator)) {
            return true;
        } else {
            std::println("Project path invalid! Must match ^[a-zA-Z0-9_-]+$ (only letters, numbers, '_' and '-')");
            return false;
        }
    });

    controller.addVariableValue("projectName", projectName);
    std::string projectPath = controller.getTargetPath() + projectName + "/";
    controller.addVariableValue("projectPath", projectPath);

    if (std::filesystem::create_directories(projectPath)) { std::println("Created {}", projectPath); }

    std::set<std::string> _noValueVars;
    std::mutex _noValueVarsLock;

    for (const auto &entry : fs::treeDirectory(selectedTemplatePath)) {
        fileProcessors.emplace_back(
            [&](const std::string &entry) {
                std::string inputFilePath = selectedTemplatePath + entry;
                std::string outputFilePath = projectPath + entry;

                std::ifstream input{inputFilePath, std::ios::in};
                if (!input.is_open()) throw std::runtime_error("Error opening file: " + inputFilePath);

                // if it is in the nested directories, create directory
                if (outputFilePath.contains("/")) {
                    auto tmp = std::filesystem::path(outputFilePath);
                    std::filesystem::create_directories(tmp.parent_path());
                }

                std::ofstream output{outputFilePath, std::ios::out | std::ios::trunc};
                if (!output.is_open()) throw std::runtime_error("Error creating file: " + outputFilePath);

                for (std::string line; std::getline(input, line);) {
                    std::regex pattern(R"(\{\{(\w+)\}\})");

                    std::string result = line;

                    for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), pattern),
                                              end = std::sregex_iterator();
                         i != end;
                         i++) {
                        const std::smatch &match = *i;
                        std::string key = match.str().substr(2, static_cast<size_t>(match.length()) - 4l);
                        auto value = controller[key];
                        if (value.has_value()) {
                            result.replace(static_cast<size_t>(match.position()),
                                           static_cast<size_t>(match.length()),
                                           value.value());
                        } else {
                            std::lock_guard<std::mutex> guard(_noValueVarsLock);
                            _noValueVars.insert(key);
                        }
                    }
                    output << result << '\n';
                }

                input.close();
                output.close();
            },
            entry);
    }

    for (auto &thread : fileProcessors) {
		if (thread.joinable()) thread.join();
	}

	std::println("Copied template {}", templateName);

    if (_noValueVars.size() != 0) {
        std::println("Vecron Variables without value detected! Please provide values for:");
        for (const auto &var : _noValueVars) { std::println("{}", var); }
    }

    return 0;
}
