#pragma once

#include "command/command.hpp"

namespace command {

class Build : public Command {
public:
    std::string label() const noexcept override { return "build"; }
    std::string description() const noexcept override { return "Builds an executable\nTo be run from vecron directory"; }

    int exec(controller::Controller &) noexcept override;
};

} // namespace command
