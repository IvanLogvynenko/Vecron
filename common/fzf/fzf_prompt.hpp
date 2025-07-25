#pragma once

#include "fzf/fzf_modes/fzf_mode.hpp"
#include "fzf_modes.hpp"
#include "fzf_prompt_helpers.hpp"

#include "util/dereferencers.hpp"
#include "util/process.hpp"
#include "util/split.hpp"

#include <algorithm>
#include <concepts>
#include <functional>
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

namespace fzf {
template <class T>
concept FzfItem = std::convertible_to<T, std::string> || HasLabel<T> ||
    HasName<T> || HasToString<T>;

template <typename Item, typename Obj>
std::string itemToString(const Item &item) {
    const Obj &option = common::util::dereference<Item>::get(item);

    if constexpr (HasLabel<Obj>)
        return option.label();
    else if constexpr (HasName<Obj>)
        return option.name();
    else if constexpr (HasToString<Obj>)
        return option.toString();
    else if constexpr (std::convertible_to<Obj, std::string>)
        return static_cast<std::string>(option);
}

template <typename Container>
Container
prompt_core(Container &&options,
            const std::initializer_list<std::shared_ptr<mode::FzfMode>> modes) {
    using Item = typename Container::value_type;
    using Obj = common::util::dereference<Item>::type;
    static_assert(FzfItem<Obj>,
                  "prompt<Container<T>>() requires T to model FzfItem");

    std::string input = "";

#ifdef ENABLE_DESCRIPTION_DETECTION
    bool enableDescriptions = false;
#endif

    for (const auto &item : options) {
#ifdef ENABLE_DESCRIPTION_DETECTION
        if constexpr (fzf::mode::HasDescription<Obj>) {
            enableDescriptions = true;
        }
#endif

        input += itemToString<Item, Obj>(item) + '\n';
    }

    std::string command = "fzf";
    for (const auto &mode : modes) { command += " " + std::string(*mode); }

//     //adding info if description method was detected
#ifdef ENABLE_DESCRIPTION_DETECTION
    if (enableDescriptions && !command.contains("--preview")) {
        command += " " + static_cast<std::string>(*(fzf::mode::info<Item>(options)));
    }
#endif

    common::util::Process p(command);

    p << input;

    std::string selections = p.run();
    std::vector<Item> result = {};

    for (const std::string &selection : common::util::split(selections, '\n'))
        for (size_t i = 0; i < options.size(); i++)
            if (itemToString<Item, Obj>(options[i]) == selection)
                result.push_back(std::move(options[i]));
    return result;
}

template <typename T>
    requires FzfItem<T>
auto prompt(
    const std::vector<T> &&options,
    const std::initializer_list<std::shared_ptr<mode::FzfMode>> &modes = {
        mode::bind(),
        mode::Style::FULL,
        mode::height(30),
        mode::reverse(),
        mode::cycle(),
    }) {
    return prompt_core(std::move(options), modes);
}

template <typename T>
    requires FzfItem<T>
auto prompt(
    std::vector<std::reference_wrapper<T>> &&options,
    const std::initializer_list<std::shared_ptr<mode::FzfMode>> &modes = {
        mode::bind(),
        mode::Style::FULL,
        mode::height(30),
        mode::reverse(),
        mode::cycle(),
    }) {
    return prompt_core<std::vector<std::reference_wrapper<T>>>(
        std::move(options), modes);
}

template <typename T>
    requires FzfItem<T>
auto prompt(
    std::vector<std::unique_ptr<T>> &&options,
    const std::initializer_list<std::shared_ptr<mode::FzfMode>> &modes = {
        mode::bind(),
        mode::Style::FULL,
        mode::height(30),
        mode::reverse(),
        mode::cycle(),
    }) {
    return prompt_core<std::vector<std::unique_ptr<T>>>(std::move(options),
                                                        modes);
}

template <typename T>
    requires FzfItem<T>
auto prompt(
    std::vector<std::shared_ptr<T>> &&options,
    const std::initializer_list<std::shared_ptr<mode::FzfMode>> &modes = {
        mode::bind(),
        mode::Style::FULL,
        mode::height(30),
        mode::reverse(),
        mode::cycle(),
    }) {
    return prompt_core<std::vector<std::shared_ptr<T>>>(std::move(options),
                                                        modes);
}

template <typename T>
    requires FzfItem<T>
auto prompt(
    std::vector<T *> &&options,
    const std::initializer_list<std::shared_ptr<mode::FzfMode>> &modes = {
        mode::bind(),
        mode::Style::FULL,
        mode::height(30),
        mode::reverse(),
        mode::cycle(),
    }) {
    return prompt_core<std::vector<T *>>(std::move(options), modes);
}

} // namespace fzf
