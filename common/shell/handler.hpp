#pragma once

namespace common::shell::handlers {

template <typename T>
concept Handler = requires(T t) {
    { t.get() };
};

template <typename T>
concept OutputHandler = requires(T t) {
    { t.getOutput() };
};

} // namespace common::shell::handlers
