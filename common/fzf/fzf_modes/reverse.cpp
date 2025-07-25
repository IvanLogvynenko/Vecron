#include "reverse.hpp"

namespace fzf::mode {

Reverse::operator std::string() const noexcept {
    return "--reverse ";
}

} // namespace fzf::mode
