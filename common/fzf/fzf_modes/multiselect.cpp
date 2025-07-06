#include "multiselect.hpp"

namespace fzf::mode {

Multiselect::operator std::vector<std::string>() const noexcept {
    if (_max == -1)
        return {"--multi"};
    else
        return {"--multi ", std::to_string(_max)};
}

} // namespace fzf::mode
