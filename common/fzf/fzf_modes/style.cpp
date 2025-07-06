#include "style.hpp"
#include <memory>

namespace fzf::mode {

std::shared_ptr<Style> Style::FULL = std::make_shared<Style>("full");
std::shared_ptr<Style> Style::MINIMAL = std::make_shared<Style>("minimal");
std::shared_ptr<Style> Style::DEFAULT = std::make_shared<Style>("default");

Style::operator std::vector<std::string>() const noexcept {
    return {"--style", this->_style};
}

} // namespace fzf::mode
