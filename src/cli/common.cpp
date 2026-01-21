#include "common.hpp"
#include "shell/shell.hpp"
#include <cstdlib>
#include <print>

namespace cli {

// void printCentered(const std::string &text, int row) {
//     // Get terminal size
//     struct winsize w;
//     if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
//         std::cerr << "Failed to get terminal size.\n";
//         return;
//     }
//
//     int cols = w.ws_col;
//
//     // Avoid overflow or wrapping
//     if (static_cast<int>(text.length()) >= cols) {
//         std::cout << text << '\n';
//         return;
//     }
//
//     int x = (cols - static_cast<int>(text.length())) / 2 + 1; // ANSI is 1-based
//     int y = row + 1; // ANSI rows are also 1-based
//
//     // Move cursor and print
//     std::cout << "\033[" << y << ";" << x << "H" << text << std::flush;
// }

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

/**
* @brief cleans stdout, stderr of the shell
*
* @warning deprecated, use special clear() method of the shell you want to clear
* @warning might not clear the shell you want as it will have to create new shell, and that shell will be clened (with vecron process stdio)
* @warning has overhead over the Shell::clear()
*/
void clear() {
    boost::asio::io_context ctx = {};
    common::shell::Shell::execute("clear", ctx, {{"TERM", std::getenv("TERM")}});
}

} // namespace cli
