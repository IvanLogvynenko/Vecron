#include "debug.hpp"
#include "config/global_config.hpp"
#include <print>

void command::Debug::execute() {
    std::println("{}", config::getGlobalConfigPath().value_or(""));
}
