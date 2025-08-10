#include "home.hpp"

std::string util::home() {
#ifdef _WIN32
    const char *homeDir = std::getenv("USERPROFILE");
#else
    const char *homeDir = std::getenv("HOME");
#endif
    return homeDir ? std::string(homeDir) + "/" : std::string();
}
