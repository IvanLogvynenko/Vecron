#pragma once

#include "command/command.hpp"

namespace command {

class Debug : public Command {
public:
    std::string label() const noexcept override { return {"debug"}; }
    std::string description() const noexcept override {
        return {"Give it a try, anything can happen"};
    }

    int exec(controller::Controller &) noexcept override;
};

} // namespace command
