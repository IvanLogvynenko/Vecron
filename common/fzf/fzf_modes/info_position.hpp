#pragma once
#include "fzf/fzf_modes/fzf_mode.hpp"
#include <memory>

namespace fzf::mode {

class InfoPosition : public FzfMode {
private:
    const std::string _position;

public:
    explicit InfoPosition(std::string position)
        : FzfMode(), _position(std::move(position)) {}

    operator std::string() const noexcept override;

    static std::shared_ptr<InfoPosition> UP, LEFT, RIGHT, DOWN;
};

} // namespace fzf::mode
