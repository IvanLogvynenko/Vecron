#pragma once

#include <boost/asio/io_context.hpp>
namespace common::shell::handlers {

template <typename T>
concept Handler = requires(T t) {
    { t.get() };
};

template <typename T>
concept Writable = requires(T t, std::string input) {
    { t.write(input) };
};

// template <typename T>
// concept StdioHandler = requires(T t) {
//     { T() };
// };
//
// template <typename T>
// concept BoostPipe = requires(T) {
//     { T(boost::asio::io_context) };
// };

} // namespace common::shell::handlers
