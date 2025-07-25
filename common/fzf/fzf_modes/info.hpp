#pragma once
#include "fzf/fzf_modes/fzf_mode.hpp"
#include "util/dereferencers.hpp"
#include <concepts>
#include <sstream>
#include <vector>

namespace fzf::mode {

template <class Item>
concept HasDescription = requires(Item t) {
    { t.description() } -> std::convertible_to<std::string>;
};

template <class Item> class Info : public FzfMode {
private:
    const std::vector<Item> &_options;

public:
    explicit Info(const std::vector<Item> &options)
        : FzfMode(), _options(options) {}

    operator std::string() const noexcept override {
        using T = common::util::dereference<Item>::type;
        std::stringstream builder{};
        builder << "'opts=(";
        for (const Item &tmp : this->_options) {
            const T &item = common::util::dereference<Item>::get(tmp);
            if constexpr (HasDescription<T>) { builder << '"' << item.description() << "\" ";
            } else if constexpr (std::same_as<std::string, T>)
                builder << '"' << item << "\" ";
            else
                builder << '"' << '"' << " ";
        }
        builder << ") && echo ${opts[{n}+1]}'";
        return "--preview " + builder.str();
    }
};

} // namespace fzf::mode
