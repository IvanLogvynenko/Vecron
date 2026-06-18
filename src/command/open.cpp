#include "command/open.hpp"
#include <print>

int command::Open::exec(controller::Controller &) noexcept {
	std::println("Using open command");
	return 0;
}
