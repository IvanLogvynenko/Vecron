#include "command/build.hpp"
#include "controller/controller.hpp"
#include <print>

int command::Build::exec(controller::Controller &controller) noexcept {
	const auto& localConfig = controller.getLocalConfig();
	std::println("Local config path: {}", localConfig.getConfigPath());
	return 0;
}


