#pragma once

#include "command.hpp"

namespace command {

class NewCommand : public Command {
public:
    NewCommand() = default;

    std::string label() const noexcept override { return {"new"}; }
    std::string description() const noexcept override {
        return {"Creates new folder with given name and formats it with already "
               "known vecron variable values"};
    }

    void execute() override;
};

} // namespace command
