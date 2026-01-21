#pragma once

#include <cstdio>

namespace common::shell::handlers {

class StdoutHandler {
public:
    constexpr auto get() { return stdout; }
};

class StderrHandler {
public:
    constexpr auto get() { return stderr; }
};

class StdinHandler {
public:
    constexpr auto get() { return stdin; }
};

} // namespace common::shell::handlers
