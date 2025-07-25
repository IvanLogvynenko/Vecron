#pragma once
#include "fzf/fzf_modes/fzf_mode.hpp"

namespace fzf::mode {

class Pattern : public FzfMode {
private:
    const std::string _pattern;

public:
    explicit Pattern(std::string pattern) : FzfMode(), _pattern(std::move(pattern)) {}

    operator std::string() const noexcept override;
};

} // namespace fzf::mode
