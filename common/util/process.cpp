#include "process.hpp"
#include "split.hpp"

#include <array>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

namespace common::util {

ProcessException::ProcessException(std::string message, unsigned code)
    : _code(code), _message(std::move(message)) {
    if (_code == 0)
        throw std::runtime_error("Well, guest what? 0 means success man");
}

const char *ProcessException::what() const noexcept {
	return this->_message.c_str();
}

Process::Process(const std::string &command) {
    auto temp = util::split(command, ' ');
    _command = temp[0];
    _args = {};
    for (size_t i = 1, till = temp.size(); i < till; i++) {
        _args.push_back(temp[i]);
    }
}

Process::Process(std::string command, std::initializer_list<std::string> argv)
    : _command(std::move(command)), _args(argv) {}

Process::Process(std::string command, std::vector<std::string> argv)
    : _command(std::move(command)), _args(std::move(argv)) {}


Process::Process(Process &&other) noexcept
    : in(std::move(other.in)), out(std::move(other.out)),
      err(std::move(other.err)), _command(std::move(other._command)),
      _args(std::move(other._args)) {}

Process &Process::operator=(Process &&other) noexcept {
    if (this != &other) {
        this->_args = std::move(other._args);
        this->_command = std::move(other._command);
        this->out = std::move(other.out);
        this->in = std::move(other.in);
        this->err = std::move(other.err);
    }
    return *this;
}

std::string Process::run() {
    std::array<int, 2> in_pipe;
    std::array<int, 2> out_pipe;
    std::array<int, 2> err_pipe;

    if (pipe(in_pipe.data()) == -1 || pipe(out_pipe.data()) == -1 ||
        pipe(err_pipe.data()) == -1) {
        throw std::runtime_error("Failed to create pipes");
    }

    pid_t pid = fork();
    if (pid == -1) { throw std::runtime_error("Failed to fork"); }

    if (pid == 0) {
        // --- Child process ---
        dup2(in_pipe[0], STDIN_FILENO);
        dup2(out_pipe[1], STDOUT_FILENO);
        dup2(err_pipe[1], STDERR_FILENO);

        close(in_pipe[1]);
        close(out_pipe[0]);
        close(err_pipe[0]);

        // Prepare arguments
        std::vector<char *> argv;
        argv.push_back(const_cast<char *>(_command.c_str()));
        for (const auto &arg : _args) {
            argv.push_back(const_cast<char *>(arg.c_str()));
        }
        argv.push_back(nullptr);

        execvp(_command.c_str(), argv.data());
        _exit(127); // If exec fails
    }

    // --- Parent process ---
    close(in_pipe[0]);
    close(out_pipe[1]);
    close(err_pipe[1]);

    // Write to child's stdin
    std::string input = in.str();
    ::write(in_pipe[1], input.data(), input.size());
    close(in_pipe[1]); // Signal EOF

    // Read from child's stdout
    std::array<char, 1024> buffer;
    ssize_t count;
    while ((count = ::read(out_pipe[0], buffer.data(), sizeof(buffer))) > 0) {
        out.write(buffer.data(), count);
    }
    close(out_pipe[0]);

    // Read from child's stderr
    while ((count = ::read(err_pipe[0], buffer.data(), sizeof(buffer))) > 0) {
        err.write(buffer.data(), count);
    }
    close(err_pipe[0]);

    // Wait for child to exit
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        throw ProcessException("Process exited with error code ",
                               WEXITSTATUS(status));
    }
    return out.str();
}

std::string Process::run(const std::string &command) {
    std::vector<std::string> input_and_command = split(command, '|');
    if (input_and_command.size() > 2)
        throw std::runtime_error("Error parsing input and command");

    Process p(input_and_command[1]);
    for (const auto &item : split(input_and_command[0], ' ')) p << item << '\n';

    return p.run();
}

} // namespace common::util
