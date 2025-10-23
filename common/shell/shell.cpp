#include "shell.hpp"
#include <iostream>
#include <array>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

namespace common::shell {

Shell::Shell(const std::string& shell) : pid(-1), is_active(false) {
    // Create pipes for stdin, stdout, stderr
    if (pipe(in_pipe.data()) == -1 || pipe(out_pipe.data()) == -1 || pipe(err_pipe.data()) == -1) {
        throw std::runtime_error("Failed to create pipes");
    }
    
    startShell(shell);
}

Shell::~Shell() {
    if (is_active) {
        execute("exit");
        close(in_pipe[0]);
        close(in_pipe[1]);
        close(out_pipe[0]);
        close(out_pipe[1]);
        close(err_pipe[0]);
        close(err_pipe[1]);
        waitpid(pid, nullptr, 0);
    }
}

void Shell::startShell(const std::string& shell_path) {
    pid = fork();
    
    if (pid == -1) {
        throw std::runtime_error("Failed to fork process");
    }
    
    if (pid == 0) {
        // Child process
        close(in_pipe[1]);  // Close write end of input pipe
        close(out_pipe[0]); // Close read end of output pipe
        close(err_pipe[0]); // Close read end of error pipe
        
        // Redirect stdin, stdout, stderr
        dup2(in_pipe[0], STDIN_FILENO);
        dup2(out_pipe[1], STDOUT_FILENO);
        dup2(err_pipe[1], STDERR_FILENO);
        
        // Close the original pipe ends
        close(in_pipe[0]);
        close(out_pipe[1]);
        close(err_pipe[1]);
        
        // Execute shell
        execl(shell_path.c_str(), shell_path.c_str(), "-i", nullptr); // Interactive mode
        exit(EXIT_FAILURE); // Only reached if execl fails
    } else {
        // Parent process
        close(in_pipe[0]);  // Close read end of input pipe
        close(out_pipe[1]); // Close write end of output pipe
        close(err_pipe[1]); // Close write end of error pipe
        is_active = true;
        
        // Wait for shell to be ready
        usleep(100000); // 100ms
    }
}

Shell::CommandResult Shell::execute(const std::string& command) {
    CommandResult result;
    
    if (!is_active) {
        result.error = "Shell is not active";
        result.exit_code = -1;
        return result;
    }
    
    // Send command to shell
    writeToPipe(command + "\n");
    
    // Read output
    result.output = readFromPipe(out_pipe[0]);
    result.error = readFromPipe(err_pipe[0]);
    
    // For simple commands, we assume success
    // In a real implementation, you'd need more sophisticated output parsing
    result.exit_code = 0;
    
    return result;
}

std::string Shell::readFromPipe(int pipe_fd) const {
    std::string result;
    char buffer[256];
    fd_set set;
    struct timeval timeout;
    
    while (true) {
        FD_ZERO(&set);
        FD_SET(pipe_fd, &set);
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000; // 100ms timeout
        
        int rv = select(pipe_fd + 1, &set, nullptr, nullptr, &timeout);
        if (rv == -1) {
            break; // Error
        } else if (rv == 0) {
            break; // Timeout
        } else {
            ssize_t count = read(pipe_fd, buffer, sizeof(buffer) - 1);
            if (count <= 0) {
                break;
            }
            buffer[count] = '\0';
            result += buffer;
        }
    }
    
    return result;
}

void Shell::writeToPipe(const std::string& data) const {
    write(in_pipe[1], data.c_str(), data.length());
}

} // namespace common::shell
