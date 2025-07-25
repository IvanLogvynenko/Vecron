#pragma once
#include "fzf/fzf_modes/fzf_mode.hpp"
#include <memory>

namespace fzf::mode {

class Style : public FzfMode {
private:
    const std::string _style;

public:
    explicit Style(std::string style) : FzfMode(), _style(std::move(style)) {}

	static std::shared_ptr<Style> FULL, MINIMAL, DEFAULT;

    operator std::string() const noexcept override;
};

} // namespace fzf::mode
