#pragma once

#include "command/command.hpp"
#include <memory>
#include <vector>

namespace command {

class NewCommand : public Command {
public:
    std::string label() const noexcept override { return {"new"}; }
    std::string description() const noexcept override {
        return {"Creates new folder with given name and formats it with already "
               "known vecron variable values"};
    }

	int exec(controller::Controller* controller) noexcept override;

	std::vector<std::unique_ptr<Command>> getCommands() const noexcept override {
		return {};
	}
};

} // namespace command
