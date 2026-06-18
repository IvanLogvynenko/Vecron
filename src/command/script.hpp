#pragma once

#include "command/command.hpp"
#include <utility>
#include <vector>

namespace command {

class Script : public command::Command {
private:
    std::vector<std::string> _script;
    std::string _name;

public:
    Script(std::string name, const std::string &) : _name(std::move(name)) {}
    std::string label() const noexcept override { return _name; }
    std::string description() const noexcept override {
        return "Builds an executable\nTo be run from vecron directory";
    }

    int exec(controller::Controller &) noexcept override { return 0; }
};

} // namespace command
