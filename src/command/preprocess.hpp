#pragma once

#include "command/command.hpp"
namespace command {

class Preprocess : public Command {
public:
    std::string label() const noexcept override { return {"preprocess"}; }
    std::string description() const noexcept override {
        return {"Preprocesses files in vecron directory\n"
                "Simple to the preprocessing in new"};
    }

    int exec(controller::Controller &) noexcept override;
};

} // namespace command
