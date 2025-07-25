#include "multiselect.hpp"

namespace fzf::mode {

Multiselect::operator std::string() const noexcept {
    if (_max.has_value())
        return "--multi";
    else
        return "--multi " + std::to_string(_max.value());
}

} // namespace fzf::mode
