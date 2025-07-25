#include "fzf_mode.hpp"

namespace fzf::mode {

class Cycle : public FzfMode {
public:
    Cycle() = default;

    operator std::string() const noexcept override;
};


} // namespace fzf::mode
