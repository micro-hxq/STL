#ifndef _STL_WT_FUNCTIONAL_HPP_
#define _STL_WT_FUNCTIONAL_HPP_

/**
 *  depend on:
 *            wt_utility.hpp
 */

namespace wt{

template <typename T = void>
struct equal_to {
    constexpr bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs == rhs;
    }
};

template <>
struct equal_to<void> {
    template <typename T, typename U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
    {
        return wt::forward<T>(lhs) == wt::forward<U>(rhs);
    }
};

template <typename T = void>
struct not_equal_to {
    constexpr bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs != rhs;
    }
};

template <>
struct not_equal_to<void> {
    template <typename T, typename U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
    {
        return wt::forward<T>(lhs) != wt::forward<U>(rhs);
    }
};

template <typename T = void>
struct greater {
    constexpr bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs > rhs;
    }
};

template <>
struct greater<void> {
    template <typename T, typename U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
    {
        return wt::forward<T>(lhs) > wt::forward<U>(rhs);
    }
};

template <typename T = void>
struct less {
    constexpr bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs < rhs;
    }
};

template <>
struct less<void> {
    template <typename T, typename U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
    {
        return wt::forward<T>(lhs) < wt::forward<U>(rhs);
    }
};

template <typename T = void>
struct great_equal {
    constexpr bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs >= rhs;
    }
};

template <>
struct great_equal<void> {
    template <typename T, typename U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
    {
        return wt::forward<T>(lhs) >= wt::forward<U>(rhs);
    }
};

template <typename T = void>
struct less_equal {
    constexpr bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs <= rhs;
    }
};

template <>
struct less_equal<void> {
    template <typename T, typename U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
    {
        return wt::forward<T>(lhs) <= wt::forward<U>(rhs);
    }
};



} // namespace wt

#endif