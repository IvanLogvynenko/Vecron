#include "new_command.hpp"
#include "controller/controller.hpp"
#include "fs/list.hpp"
#include "fzf/fzf_prompt.hpp"
#include <string>
#include <thread>
#include <print>

int command::NewCommand::exec(controller::Controller* controller) noexcept {
	const std::string templatesPath = controller->getGlobalConfig().getTemplatePath();
	std::vector<std::string> data = fzf::prompt(fs::listDirectories(templatesPath));
	std::vector<std::thread> fileProcessors{};

	for (const auto& entry : fs::treeDirectory(templatesPath + data[0])) {
		fileProcessors.emplace_back([&](const std::string& entry) {
			std::println("{} -> {}", templatesPath + data[0], controller->getTargetPath() + entry);

		}, entry);
	}

	return 0;
}
