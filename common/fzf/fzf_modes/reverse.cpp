#include "reverse.hpp"

namespace fzf::mode {

Reverse::operator std::vector<std::string>() const noexcept {
    return {"--reverse"};
}

} // namespace fzf::mode
