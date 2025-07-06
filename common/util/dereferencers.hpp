#pragma once

#include <functional>
#include <memory>

namespace util {

template <typename T> struct dereference {
    using type = T;
    static T &get(T &t) { return t; }
};

template <typename T> struct dereference<std::reference_wrapper<T>> {
    using type = T;
    static T &get(const std::reference_wrapper<T> &t) { return t.get(); }
};

template <typename T> struct dereference<std::unique_ptr<T>> {
    using type = T;
    static T &get(const std::unique_ptr<T> &t) { return *t; }
};

template <typename T> struct dereference<std::shared_ptr<T>> {
    using type = T;
    static T &get(const std::shared_ptr<T> &t) { return *t; }
};

template <typename T> struct dereference<T *> {
    using type = T;
    static T &get(const T *t) { return *t; }
};

} // namespace util
