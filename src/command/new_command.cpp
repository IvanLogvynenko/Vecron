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
	
	controller.lockDataBase();
    for (const auto &entry : fs::treeDirectory(selectedTemplatePath)) {
        fileProcessors.emplace_back(
            [&](const std::string &entry) {
                std::string inputFilePath = selectedTemplatePath + entry;
                std::string outputFilePath = projectPath + entry;

                std::ifstream inputFile{inputFilePath, std::ios::in};
                if (!inputFile.is_open()) throw std::runtime_error("Error opening file: " + inputFilePath);

                // if it is in the nested directories, create directory
                if (outputFilePath.contains("/")) {
                    auto tmp = std::filesystem::path(outputFilePath);
                    std::filesystem::create_directories(tmp.parent_path());
                }

                std::ofstream outputFile{outputFilePath, std::ios::out | std::ios::trunc};
                if (!outputFile.is_open()) throw std::runtime_error("Error creating file: " + outputFilePath);
				
				auto noValueVars = controller.preprocessStringstream(inputFile, outputFile);
                
                inputFile.close();
                outputFile.close();

				std::lock_guard<std::mutex> guard(_noValueVarsLock);
				_noValueVars.insert_range(noValueVars);
            },
            entry);
    }
    for (auto &thread : fileProcessors) {
        if (thread.joinable()) thread.join();
    }

	controller.unlockDataBase();

    std::println("Copied template {}", templateName);

    if (_noValueVars.size() != 0) {
        std::println("Vecron Variables without value detected! Please provide values for:");
        for (const auto &var : _noValueVars) { std::println("{}", var); }
    }

    return 0;
}
