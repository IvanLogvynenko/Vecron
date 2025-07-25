#pragma once
#include <string>

namespace fzf::mode {

class FzfMode {
public:
	FzfMode() = default;
    virtual operator std::string() const noexcept = 0;
    virtual ~FzfMode() = default;

    FzfMode(const FzfMode &) = default;
    FzfMode(FzfMode &&) = default;
    FzfMode &operator=(const FzfMode &) = delete;
    FzfMode &operator=(FzfMode &&) = delete;
};

} // namespace fzf::mode
