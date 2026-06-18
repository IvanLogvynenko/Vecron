#pragma once

#include <string>

namespace controller {
class Controller;

} // namespace controller

namespace command {

class Command {
public:
    Command() = default;

    Command(const Command &) = delete;
    Command(Command &&) = default;
    Command &operator=(const Command &) = delete;
    Command &operator=(Command &&) = default;

    virtual ~Command() = default;

    virtual std::string label() const noexcept = 0;
    virtual std::string description() const noexcept = 0;

    virtual int exec(controller::Controller &) noexcept = 0;
};

} // namespace command
