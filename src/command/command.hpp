#pragma once

#include <string>

namespace command {

class Command {
public:
    Command() = default;
    virtual ~Command() = default;

    virtual std::string label() const noexcept = 0;
    virtual std::string description() const noexcept = 0;

    virtual void execute() = 0;
};

} // namespace command
