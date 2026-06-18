#include "command_tree.hpp"
#include "command/command.hpp"
#include "util/split.hpp"

#include <algorithm>
#include <format>
#include <memory>
#include <stdexcept>

namespace command {

CommandNode::CommandNode(CommandNode &&node) noexcept {
    if (this == &node) { return; }
    this->_label = std::move(node._label);
    this->_command = std::move(node._command);
    this->_followers = std::move(node._followers);
};
CommandNode &CommandNode::operator=(CommandNode &&node) noexcept {
    if (this != &node) {
        this->_label = std::move(node._label);
        this->_command = std::move(node._command);
        this->_followers = std::move(node._followers);
    }
    return *this;
}

void CommandNode::addFollower(const std::string &path, CommandNode commandNode) {
    if (path != " " && path != commandNode._label) {
        auto split = common::util::split(path, ' ');
        this->addFollower(std::queue{split.begin(), split.end()}, std::move(commandNode));
    } else {
        auto insert_position = std::ranges::lower_bound(this->_followers, commandNode._label, {}, &CommandNode::_label);
        this->_followers.insert(insert_position, std::move(commandNode));
    }
}
void CommandNode::addFollower(std::queue<std::string> path, CommandNode commandNode) {
    if (path.size() == 0) { throw std::runtime_error("command path queue is empty"); }

    // Use of raw pointers, no memory allocations that are unsafe as pointers point to the memory controlled by unique_ptr
    CommandNode *current = this;
    while (path.size() != 1) { // Insert/search nodes till the last
        CommandNode &searchResult = current->findFollower(path.front());
        if (searchResult._label != path.front()) {
            current->addFollower(path.front(), CommandNode{path.front()});
			current = &findFollower(path.front());
        } else {
            current = &searchResult;
        }
        path.pop();
    }

    // TODO: find efficient way of printing an alredy existing path
    // problem: now to print path it would be needed to join all entries in path queue (takes time) and store them(memory overhead)
    auto searchPosition = std::ranges::lower_bound(current->_followers, path.front(), {}, &CommandNode::_label);
    if (searchPosition != current->_followers.end() && searchPosition->_label == path.front()) {
        throw std::runtime_error(std::format("command by this path already exists, ends on {}", path.front()));
    }
    current->_followers.insert(searchPosition, std::move(commandNode));
}

CommandNode &CommandNode::findFollower(const std::string &name) {
    auto searchResult = std::ranges::lower_bound(this->_followers, name, {}, &CommandNode::_label);
    if (searchResult == this->_followers.end()) {
        throw std::runtime_error("The passed value is not found in the tree. Fzf user input filtering failed");
    }
    return *searchResult;
}

int CommandNode::exec(controller::Controller &controller) {
    if (this->isExecutable()) {
        return this->_command->exec(controller);
    } else {
        throw std::runtime_error("Called exec on the nonexcutable node");
    }
}

} // namespace command
