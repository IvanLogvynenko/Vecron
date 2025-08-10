#pragma once

#include <memory>
#include <string>
#include <vector>

namespace controller {
class Controller;

} // namespace controller

namespace command {

class Command {
public:
    Command() = default;

    Command(const Command &) = default;
    Command(Command &&) = delete;
    Command &operator=(const Command &) = default;
    Command &operator=(Command &&) = delete;

    virtual ~Command() = default;

    virtual std::string label() const noexcept = 0;
    virtual std::string description() const noexcept = 0;

    virtual std::vector<std::unique_ptr<Command>>
    getCommands() const noexcept = 0;
    virtual int exec(controller::Controller *) noexcept = 0;
};

} // namespace command
