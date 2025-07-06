#pragma once
#include "fzf/fzf_modes/fzf_mode.hpp"

namespace fzf::mode {

class Multiselect : public FzfMode {
private:
    const int _max;

public:
    explicit Multiselect(int max = -1) : FzfMode(), _max(max) {}

    operator std::vector<std::string>() const noexcept override;
};

} // namespace fzf::mode
