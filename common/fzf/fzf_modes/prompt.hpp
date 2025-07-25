#pragma once
#include "fzf/fzf_modes/fzf_mode.hpp"

namespace fzf::mode {

class Prompt : public FzfMode {
private:
    const std::string _pattern;

public:
    explicit Prompt(std::string pattern) : FzfMode(), _pattern(std::move(pattern)) {}	

    operator std::string() const noexcept override;
};

} // namespace fzf::mode
