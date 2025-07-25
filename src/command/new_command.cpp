#include "new_command.hpp"
#include "fs/list.hpp"
#include "fzf/fzf_prompt.hpp"
#include <print>
#include <string>
#include <thread>

void command::NewCommand::execute() {
	const std::string templatesPath = "/home/ivan/.config/vecron/templates/";
	std::vector<std::string> data = fzf::prompt(fs::listDirectories(templatesPath));
	std::vector<std::thread> fileProcessors{};

	for (const auto& entry : fs::treeDirectory(templatesPath + data[0])) {
		// std::println("{}\n{}", entry, templatesPath + data[0]);
		fileProcessors.emplace_back([](const std::string&) {

		}, entry);
	}
}
