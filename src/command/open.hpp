#pragma once

#include "command/command.hpp"
namespace command {

class Open : public Command {
public:
    std::string label() const noexcept override { return {"open"}; }
    std::string description() const noexcept override {
        return {"Preprocesses files in vecron directory\n"
                "Simple to the preprocessing in new"};
    }

    int exec(controller::Controller &) noexcept override;
};

} // namespace command
