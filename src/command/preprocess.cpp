#include "command/preprocess.hpp"
#include "controller/controller.hpp"
#include "fs/list.hpp"

#include <fstream>
#include <mutex>
#include <print>
#include <set>
#include <thread>
#include <sstream>

int command::Preprocess::exec(controller::Controller &controller) noexcept {
    std::vector<std::thread> fileProcessors{};

    std::set<std::string> _noValueVars;
    std::mutex _noValueVarsLock;

	controller.lockDataBase();
    for (const auto &entry : fs::treeDirectory(controller.getTargetPath())) {
        fileProcessors.emplace_back(
            [&](const std::string &entry) {
                std::string filePath = controller.getTargetPath() + entry;

                // First read the entire file content
                std::ifstream input{filePath, std::ios::in};
                if (!input.is_open()) throw std::runtime_error("Error opening file: " + filePath);
                
                std::stringstream inBuffer;
                inBuffer << input.rdbuf();
                input.close();
                std::ofstream output{filePath, std::ios::out | std::ios::trunc};
                if (!output.is_open()) throw std::runtime_error("Error creating file: " + filePath);

				auto noValuesVars = controller.preprocessStringstream(inBuffer, output);
				std::lock_guard<std::mutex> lock(_noValueVarsLock);
				_noValueVars.insert_range(noValuesVars);

				inBuffer.flush();
                output.close();
            },
            entry);
    }

    for (auto &thread : fileProcessors) {
        if (thread.joinable()) thread.join();
    }
	controller.unlockDataBase();

    if (_noValueVars.size() != 0) {
        std::println("Vecron Variables without value detected! Please provide values for:");
        for (const auto &var : _noValueVars) { std::println("{}", var); }
    }
    return 0;
}

