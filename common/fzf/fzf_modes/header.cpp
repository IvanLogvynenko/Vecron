#include "header.hpp"

namespace fzf::mode {

Header::operator std::string() const noexcept {
    return "--header=" + this->_header;
}

} // namespace fzf::mode
