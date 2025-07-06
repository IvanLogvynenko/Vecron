#pragma once
#include "fzf/fzf_modes/bind.hpp"
#include "fzf/fzf_modes/cycle.hpp"
#include "fzf/fzf_modes/header.hpp"
#include "fzf/fzf_modes/height.hpp"
#include "fzf/fzf_modes/info.hpp"
#include "fzf/fzf_modes/infoPosition.hpp"
#include "fzf/fzf_modes/multiselect.hpp"
#include "fzf/fzf_modes/pattern.hpp"
#include "fzf/fzf_modes/prompt.hpp"
#include "fzf/fzf_modes/reverse.hpp"
#include "fzf/fzf_modes/style.hpp"

namespace fzf::mode {

std::shared_ptr<Bind>
bind(std::string bind = "tab:down,shift-tab:up,ctrl-s:select,"
                        "ctrl-a:select-all,ctrl-d:deselect");
std::shared_ptr<Cycle> cycle();

std::shared_ptr<Header> header(std::string header);

std::shared_ptr<Height> height(uint8_t height);

//forward declare Info
template <class T> class Info;
template <class T> std::shared_ptr<Info<T>> info(const std::vector<T> &info) {
    return std::make_shared<Info<T>>(info);
}

std::shared_ptr<InfoPosition> infoPosition(std::string position);

std::shared_ptr<Multiselect> multiselect(int max = -1);

std::shared_ptr<Pattern> pattern(std::string pattern);

std::shared_ptr<Prompt> prompt(std::string pattern);

std::shared_ptr<Reverse> reverse();

std::shared_ptr<Style> style(std::string style);

} // namespace fzf::mode


