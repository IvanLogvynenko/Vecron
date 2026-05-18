#include "command/build.hpp"
#include "controller/controller.hpp"
#include "shell/process.hpp"
#include <print>

int command::Build::exec(controller::Controller &controller) noexcept {
    auto &localConfig = controller.getLocalConfig();
    const auto &buildCMD = localConfig.getBuildCMD();
    if (buildCMD.has_value()) {
        auto process = controller.getShell().execute(buildCMD.value());
        return process->run();
    } else {
        std::println("Error: no build method was provided");
        return 1;
    }
    return 0;
}
