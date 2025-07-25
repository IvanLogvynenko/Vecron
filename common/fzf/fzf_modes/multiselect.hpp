#pragma once
#include "fzf/fzf_modes/fzf_mode.hpp"
#include <optional>

namespace fzf::mode {

class Multiselect : public FzfMode {
private:
    const std::optional<int> _max;

public:
	explicit Multiselect() = default;
    explicit Multiselect(int max) : FzfMode(), _max(max) {}

    operator std::string() const noexcept override;
};

} // namespace fzf::mode
