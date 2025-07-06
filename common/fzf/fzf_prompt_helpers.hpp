#pragma once

#include "fzf/fzf_modes/fzf_mode.hpp"
#include "fzf_modes.hpp"
#include <memory>
#include <vector>

namespace fzf {

inline std::vector<std::shared_ptr<fzf::mode::FzfMode>> default_modes() {
    return {
        mode::bind(),
        mode::Style::FULL,
        mode::height(30),
        mode::reverse(),
        mode::cycle(),
    };
}

template <class T>
concept HasName = requires(T t) {
    { t.name() } -> std::same_as<std::string>;
};

template <class T>
concept HasLabel = requires(T t) {
    { t.label() } -> std::same_as<std::string>;
};

template <class T>
concept HasToString = requires(T t) {
    { t.toString() } -> std::same_as<std::string>;
};

} // namespace fzf
