#pragma once
#include "fzf/fzf_modes/fzf_mode.hpp"
#include <algorithm>
#include <cstdint>

namespace fzf::mode {

class Height : public FzfMode {
private:
    const int _height;

public:
    explicit Height(int height) : FzfMode(), _height(std::clamp(height, 0, 100)) {}

    operator std::string() const noexcept override;
};

} // namespace fzf::mode
