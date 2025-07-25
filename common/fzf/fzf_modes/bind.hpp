#pragma once
#include "fzf/fzf_modes/fzf_mode.hpp"

namespace fzf::mode {

class Bind : public FzfMode {
private:
    const std::string _binds;

public:
    explicit Bind(std::string binds) : FzfMode(), _binds(std::move(binds)) {}

    operator std::string() const noexcept override;
};

} // namespace fzf::mode
