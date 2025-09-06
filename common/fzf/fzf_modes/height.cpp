#include "height.hpp"
#include <string>

namespace fzf::mode {

Height::operator std::string() const noexcept {
    return "--height " + std::to_string(this->_height);
}

} // namespace fzf::mode
