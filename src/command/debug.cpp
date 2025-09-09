#include "debug.hpp"
#include "cli/common.hpp"
#include "controller/controller.hpp"
#include <print>

int command::Debug::exec(controller::Controller &controller) noexcept {
    cli::clear();
    std::println("template path: {}", controller.getGlobalConfig().getTemplatePath());
    for (auto &[key, value] : controller.getAllVariables()) std::println("key: {}, value: {}", key, value);
    return 0;
}
