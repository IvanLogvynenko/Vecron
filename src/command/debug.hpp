#pragma once

#include "command/command.hpp"
#include "controller/controller.hpp"
#include <memory>

namespace command {

class Debug : public Command {
public:
    std::string label() const noexcept override { return {"debug"}; }
    std::string description() const noexcept override {
        return {"Give it a try, anything can happen"};
    }

    int exec(controller::Controller *) noexcept override;

    std::vector<std::unique_ptr<Command>> getCommands() const noexcept override {
        return {};
    }
};

} // namespace command
