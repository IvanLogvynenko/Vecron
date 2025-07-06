#include "height.hpp"
#include <cstdint>
#include <string>

namespace fzf::mode {

uint8_t
Height::border(uint8_t value, uint8_t bottom, uint8_t up) const noexcept {
    if (value < bottom)
        return bottom;
    else if (value > up)
        return up;
    else
        return value;
}

Height::operator std::vector<std::string>() const noexcept {
    return {"--height", std::to_string(this->_height)};
}

} // namespace fzf::mode
