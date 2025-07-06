#include "prompt.hpp"

namespace fzf::mode {

Prompt::operator std::vector<std::string>() const noexcept {
    return {std::string("--prompt=") + this->_pattern};
}

} // namespace fzf::mode
