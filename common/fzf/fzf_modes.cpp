#include "fzf_modes.hpp"
#include "fzf/fzf_modes/style.hpp"
#include <memory>

namespace fzf::mode {

std::shared_ptr<Bind> bind(std::string binds) {
    return std::make_shared<Bind>(std::move(binds));
}

std::shared_ptr<Cycle> cycle() { return std::make_shared<Cycle>(); }

std::shared_ptr<Header> header(std::string header) {
    return std::make_shared<Header>(std::move(header));
}

std::shared_ptr<Height> height(uint8_t height) {
    return std::make_shared<Height>(height);
}

std::shared_ptr<InfoPosition> infoPosition(std::string position) {
    return std::make_shared<InfoPosition>(std::move(position));
}

std::shared_ptr<Multiselect> multiselect(int max) {
    return std::make_shared<Multiselect>(max);
}

std::shared_ptr<Pattern> pattern(std::string pattern) {
    return std::make_shared<Pattern>(std::move(pattern));
}

std::shared_ptr<Prompt> prompt(std::string prompt) {
    return std::make_shared<Prompt>(std::move(prompt));
}

std::shared_ptr<Reverse> reverse() { return std::make_shared<Reverse>(); }

std::shared_ptr<Style> style(std::string style) {
    return std::make_shared<Style>(std::move(style));
}

} // namespace fzf::mode

