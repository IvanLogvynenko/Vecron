#pragma once

#include <string>
#include <array>
#include <unistd.h>
#include <sys/wait.h>

namespace common::shell {

class Shell {
private:
	std::array<int, 2> in_pipe;
    std::array<int, 2> out_pipe;
    std::array<int, 2> err_pipe;
    pid_t pid;
    bool is_active;

public:
    struct CommandResult {
        int exit_code;
        std::string output;
        std::string error;
        bool success() const { return exit_code == 0; }
    };

    Shell(const std::string& shell = "/bin/sh");
    ~Shell();

    CommandResult execute(const std::string& command);
    bool isActive() const { return is_active; }

private:
    void startShell(const std::string& shell_path);
    std::string readFromPipe(int pipe_fd) const;
    void writeToPipe(const std::string& data) const;
};

} // namespace common::shell
