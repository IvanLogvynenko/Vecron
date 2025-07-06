#include "cycle.hpp"

namespace fzf::mode {

Cycle::operator std::vector<std::string>() const noexcept {
    return {"--cycle"};
}

} // namespace fzf::mode
