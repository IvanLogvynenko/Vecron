#include "shell/shell.hpp"
#include <gtest/gtest.h>

#include <boost/asio.hpp>
#include <print>

TEST(SHELL, PRINT_HELLO) {
    boost::asio::io_context ctx;
    common::shell::Shell shell{ctx, {{"DATA", "5"}}};
    auto process = shell.execute("echo $DATA");
    std::array<char, 256> buffer;
    boost::system::error_code ec;
    // size_t n = process->getOutPipe().read_some(boost::asio::buffer(buffer), ec);
    // if (!ec) {
    //     std::println("N: {}", n);
    //     for (size_t i = 0; i < n; i++) { std::print("{}", buffer[i]); }
    // } else {
    //     std::println("Error: {}", ec.message());
    // }
    std::println("Return code: {}", process->run());
}
