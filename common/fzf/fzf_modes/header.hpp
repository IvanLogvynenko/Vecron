#pragma once
#include "fzf/fzf_modes/fzf_mode.hpp"

namespace fzf::mode {

class Header : public FzfMode {
private:
    const std::string _header;

public:
    explicit Header(std::string header) : FzfMode(), _header(std::move(header)) {}

    operator std::vector<std::string>() const noexcept override;
};


} // namespace fzf::mode
