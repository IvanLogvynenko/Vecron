#include "debug.hpp"
#include "controller/controller.hpp"
#include <print>

int command::Debug::exec(controller::Controller*) noexcept {
	// std::println("template path: {}", controller->getGlobalConfig().getTemplatePath());
	std::println("some");
	return 0;
}
