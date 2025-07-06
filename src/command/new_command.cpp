#include "new_command.hpp"
#include "fs/list.hpp"
#include "fzf/fzf_prompt.hpp"
#include "util/process.hpp"
#include <filesystem>
#include <print>
#include <string>

void command::NewCommand::execute() {
	const std::string templatesPath = "/home/ivan/.config/vecron/templates/";
	std::vector<std::string> data = fzf::prompt(fs::listDirectories(templatesPath));
	for (const auto& entry : fs::listFiles(templatesPath + data[0])) {
		std::println("{}", entry);
	}

}
