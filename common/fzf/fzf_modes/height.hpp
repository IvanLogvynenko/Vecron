#pragma once
#include "fzf/fzf_modes/fzf_mode.hpp"
#include <cstdint>

namespace fzf::mode {

class Height : public FzfMode {
private:
    const uint8_t _height;

    uint8_t
    border(uint8_t value, uint8_t bottom = 0, uint8_t up = 100) const noexcept;

public:
    explicit Height(uint8_t height) : FzfMode(), _height(border(height)) {}

    operator std::vector<std::string>() const noexcept override;
};

} // namespace fzf::mode
