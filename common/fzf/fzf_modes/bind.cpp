#include "bind.hpp"
#include <string>

namespace fzf::mode {

Bind::operator std::string() const noexcept {
    return "--bind " + this->_binds;
}

} // namespace fzf::mode
