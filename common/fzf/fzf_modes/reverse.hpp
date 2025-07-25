#pragma once
#include "fzf/fzf_modes/fzf_mode.hpp"

namespace fzf::mode {

class Reverse : public FzfMode {
public:
    explicit Reverse() = default;

    operator std::string() const noexcept override;
};

} // namespace fzf::mode
