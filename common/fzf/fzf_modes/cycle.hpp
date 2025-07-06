#include "fzf_mode.hpp"
#include <vector>

namespace fzf::mode {

class Cycle : public FzfMode {
public:
    Cycle() = default;

    operator std::vector<std::string>() const noexcept override;
};


} // namespace fzf::mode
