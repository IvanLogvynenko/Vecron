#pragma once

#include "command/command.hpp"
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>

namespace command {

class CommandTree;

class CommandNode {
protected:
    std::string _label;
    std::unique_ptr<command::Command> _command;
    std::vector<CommandNode> _followers;

protected:
    void addFollower(std::queue<std::string>, CommandNode);

public:
    CommandNode() = default;
    CommandNode(std::string label) : _label(std::move(label)), _command(nullptr), _followers() {}
    CommandNode(std::unique_ptr<command::Command> command)
        : _label(command->label()), _command(std::move(command)), _followers() {}

    CommandNode(CommandNode &&node) noexcept;
    CommandNode &operator=(CommandNode &&node) noexcept;

    // Inserts new node in the command tree. Multistep path is to be separated with spaces.
    // if the (last) step and command->label() are equal, (last) step will be ommited.
    void addFollower(const std::string &, CommandNode);
    CommandNode &findFollower(const std::string &);

    std::string label() const noexcept { return this->_label; }
    std::string description() const noexcept { return this->_command ? this->_command->description() : ""; }
    inline bool isExecutable() const noexcept { return this->_command != nullptr; }

    inline const std::vector<CommandNode> &getNodes() const noexcept { return this->_followers; }
    inline std::vector<CommandNode> &&obtainNodes() noexcept { return std::move(this->_followers); }

    int exec(controller::Controller &);
};

class CommandTree {
private:
    // Root node is an empty node that is not executable
    CommandNode _root;

public:
    CommandTree() : _root{} {}
    CommandTree(CommandNode &&node) : _root(std::move(node)) {}
    void addCommand(const std::string &path, std::unique_ptr<command::Command> command) {
        _root.addFollower(path, CommandNode{std::move(command)});
    }

	inline CommandNode& getRoot() noexcept {
		return this->_root;
	}

    inline const std::vector<CommandNode> &getCommands() const noexcept {
        return this->_root.getNodes();
    }
    // WARINING: This method can only be called once. It intended usage is to move the array to the fzf prompt function and retrieve user selection
    // to get access to the command list available in the next step, please use getCommands()
    inline std::vector<CommandNode> &&obtainCommands() noexcept {
        return std::move(this->_root.obtainNodes());
    }
};

} // namespace command
