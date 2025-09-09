#include "command/build.hpp"
#include "controller/controller.hpp"
#include "util/process.hpp"
#include <print>

int command::Build::exec(controller::Controller &controller) noexcept {
    const auto &localConfig = controller.getLocalConfig();
    const auto &buildCMD = localConfig.getBuildCMD();
    if (buildCMD.has_value()) {
        std::println("{}", common::util::Process::run(buildCMD.value()));
    } else {
		std::println("Error: no build method was provided");
		return 1;
    }
    return 0;
}
