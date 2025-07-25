#include "pattern.hpp"

namespace fzf::mode {

Pattern::operator std::string() const noexcept {
    return "--filter " + this->_pattern;
}

} // namespace fzf::mode
