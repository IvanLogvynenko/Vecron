#include "common.hpp"
#include "shell/process.hpp"
#include <iostream>
#include <print>
#include <sys/ioctl.h>
#include <unistd.h>

namespace cli {

void printCentered(const std::string &text, int row) {
    // Get terminal size
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        std::cerr << "Failed to get terminal size.\n";
        return;
    }

    int cols = w.ws_col;

    // Avoid overflow or wrapping
    if (static_cast<int>(text.length()) >= cols) {
        std::cout << text << '\n';
        return;
    }

    int x = (cols - static_cast<int>(text.length())) / 2 + 1; // ANSI is 1-based
    int y = row + 1; // ANSI rows are also 1-based

    // Move cursor and print
    std::cout << "\033[" << y << ";" << x << "H" << text << std::flush;
}

void printLogo() {
	// TODO make self adjustable logo centering
	std::println("\t\t\t\t╔══════════════════════════════════════════════════════╗");
	std::println("\t\t\t\t║ ██╗   ██╗███████╗ ██████╗██████╗  ██████╗ ███╗   ██╗ ║");
	std::println("\t\t\t\t║ ██║   ██║██╔════╝██╔════╝██╔══██╗██╔═══██╗████╗  ██║ ║");
	std::println("\t\t\t\t║ ██║   ██║█████╗  ██║     ██████╔╝██║   ██║██╔██╗ ██║ ║");
	std::println("\t\t\t\t║ ╚██╗ ██╔╝██╔══╝  ██║     ██╔══██╗██║   ██║██║╚██╗██║ ║");
	std::println("\t\t\t\t║  ╚████╔╝ ███████╗╚██████╗██║  ██║╚██████╔╝██║ ╚████║ ║");
	std::println("\t\t\t\t║   ╚═══╝  ╚══════╝ ╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝ ║");
	std::println("\t\t\t\t╚══════════════════════════════════════════════════════╝");
}

void clear() {
	common::shell::Process::run("clear");
}

} // namespace cli
