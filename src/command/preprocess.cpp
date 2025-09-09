#include "command/preprocess.hpp"
#include "controller/controller.hpp"
#include "fs/list.hpp"

#include <fstream>
#include <print>
#include <regex>
#include <set>
#include <thread>
#include <sstream>

int command::Preprocess::exec(controller::Controller &controller) noexcept {
    std::vector<std::thread> fileProcessors{};

    std::set<std::string> _noValueVars;
    std::mutex _noValueVarsLock;

    for (const auto &entry : fs::treeDirectory(controller.getTargetPath())) {
        fileProcessors.emplace_back(
            [&](const std::string &entry) {
                std::string filePath = controller.getTargetPath() + entry;

                // First read the entire file content
                std::ifstream input{filePath, std::ios::in};
                if (!input.is_open()) throw std::runtime_error("Error opening file: " + filePath);
                
                std::stringstream buffer;
                buffer << input.rdbuf();
                std::string content = buffer.str();
                input.close();

                // Process the content
                std::regex pattern(R"(\{\{(\w+)\}\})");
                std::string result;
                
                size_t lastPos = 0;
                for (std::sregex_iterator i = std::sregex_iterator(content.begin(), content.end(), pattern),
                                        end = std::sregex_iterator();
                    i != end;
                    i++) {
                    const std::smatch &match = *i;
                    std::string key = match.str().substr(2, static_cast<size_t>(match.length()) - 4l);

                    result.append(content, lastPos, static_cast<size_t>(match.position()) - lastPos);

                    auto value = controller[key];
                    if (value.has_value()) {
                        result.append(value.value());
                    } else {
                        std::lock_guard<std::mutex> guard(_noValueVarsLock);
                        _noValueVars.insert(key);
                        result.append(match.str());
                    }
                    lastPos = static_cast<size_t>(match.position()) + static_cast<size_t>(match.length());
                }
                result.append(content, lastPos, content.size() - lastPos);

                // Then write the processed content back to the file
                std::ofstream output{filePath, std::ios::out | std::ios::trunc};
                if (!output.is_open()) throw std::runtime_error("Error creating file: " + filePath);
                output << result;
                output.close();
            },
            entry);
    }

    for (auto &thread : fileProcessors) {
        if (thread.joinable()) thread.join();
    }

    if (_noValueVars.size() != 0) {
        std::println("Vecron Variables without value detected! Please provide values for:");
        for (const auto &var : _noValueVars) { std::println("{}", var); }
    }
    return 0;
}

