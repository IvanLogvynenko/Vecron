#include "infoPosition.hpp"
#include <memory>

namespace fzf::mode {

std::shared_ptr<InfoPosition> InfoPosition::UP = std::make_shared<InfoPosition>("up");
std::shared_ptr<InfoPosition> InfoPosition::DOWN = std::make_shared<InfoPosition>("down");
std::shared_ptr<InfoPosition> InfoPosition::RIGHT = std::make_shared<InfoPosition>("right");
std::shared_ptr<InfoPosition> InfoPosition::LEFT = std::make_shared<InfoPosition>("left");

InfoPosition::operator std::string() const noexcept {
    return std::string("--preview-window=") + this->_position;
}

} // namespace fzf::mode
