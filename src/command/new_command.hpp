#pragma once

#include "command/command.hpp"

namespace command {

class NewCommand : public Command {
public:
    std::string label() const noexcept override { return {"new"}; }
    std::string description() const noexcept override {
        return {"Creates new folder with given name and formats it with "
                "already known vecron variable values"};
    }

    int exec(controller::Controller &) noexcept override;
};

} // namespace command
