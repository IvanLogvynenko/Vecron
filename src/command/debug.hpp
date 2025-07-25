#pragma once

#include "command.hpp"

namespace command {

class Debug : public Command {
public:
    Debug() = default;

    std::string label() const noexcept override { return {"debug"}; }
    std::string description() const noexcept override {
        return {"Give it a try, anything can happen"};
    }

    void execute() override;
};

} // namespace command
