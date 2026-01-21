#include "shell/shell.hpp"
#include "shell/handlers/boost_pipes_handlers.hpp"
#include "shell/handlers/string_handler.hpp"
#include <gtest/gtest.h>

#include <array>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <cstdlib>
#include <print>

namespace csh = common::shell::handlers;

TEST(SHELL, PRINT_HELLO_STDIO) {
    boost::asio::io_context ctx;
    common::shell::Shell shell{ctx, {{"DATA", "5"}}};

    auto process = shell.execute("echo $DATA");

    std::println("Return code: {}", process->run());
}

TEST(SHELL, PRINT_HELLO_BOOST_PIPES) {
    boost::asio::io_context ctx;
    common::shell::Shell shell{ctx, {{"DATA", "5"}}};

    auto process = shell.execute<csh::InPipeHandler, csh::ErrPipeHandler, csh::OutPipeHandler>("echo $DATA");

    boost::process::error_code ec;
    std::array<char, 256> buf;

    size_t n = process->getOut().get().read_some(boost::asio::buffer(buf), ec);
    if (!ec) {
        std::println("N: {}", n);
        for (size_t i = 0; i < n; i++) { std::print("{}", buf[i]); }
    } else {
        std::println("Error: {}", ec.message());
    }

    std::println("Return code: {}", process->run());
}

TEST(SHELL, PRINT_HELLO_BOOST_PIPES_STRINGS) {
    boost::asio::io_context ctx;
    common::shell::Shell shell{ctx, {{"DATA", "5"}}};

    auto process = shell.execute<csh::InPipeHandler, csh::ErrPipeHandler, csh::OutStringHandler>("echo $DATA");

    auto &out = process->getOut();
    while (!out.eof()) { std::println("{}", out.getLine()); }

    std::println("Return code: {}", process->run());
}

TEST(SHELL, LIST_CURRENT_DIRECTORY_BOOST_PIPES_STRINGS) {
    boost::asio::io_context ctx;
    common::shell::Shell shell{ctx, {{"DATA", "5"}}};

    auto process = shell.execute<csh::InPipeHandler, csh::ErrPipeHandler, csh::OutStringHandler>("ls -la");

    auto &out = process->getOut();
    while (!out.eof()) { std::println("{}", out.getLine()); }

    std::println("Return code: {}", process->run());
}

TEST(SHELL, CLEAR) {
    boost::asio::io_context ctx;
    common::shell::Shell shell{ctx, {{"DATA", "5"}, {"TERM", std::getenv("TERM")}}};
	shell.clear();
}

TEST(SHELL, FZF) {
    boost::asio::io_context ctx;
    common::shell::Shell shell{ctx, {}};

    auto process = shell.execute<csh::InStringHandler, csh::ErrStringHandler, csh::OutStringHandler>("fzf");
    process->getIn().write("1\n");
    process->getIn().write("2\n");
    process->getIn().write("3\n");
    process->getIn().write("4\n");

    auto &err = process->getErr();
    while (!err.eof()) { std::println("{}", err.getLine()); }

    auto &out = process->getOut();
    while (!out.eof()) { std::println("{}", out.getLine()); }

    std::println("Return code: {}", process->run());
}
