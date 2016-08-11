#ifndef _STL_WT_FUNCTIONAL_HPP_
#define _STL_WT_FUNCTIONAL_HPP_

namespace wt{





/**
 *  Arithmetic Operations
 */
template <typename T = void>
struct plus {
    constexpr T operator()(const T& lhs, const T& rhs) const
    {
        return lhs + rhs;
    }
};

template <>
struct plus<void> {
    template <typename T, typename U>
    constexpr T operator()(T&& lhs, U&& rhs) const
    {
        return wt::forward<T>(lhs) + wt::forward<U>(rhs);
    }
};

template <typename T = void>
struct minus {
    constexpr T operator()(const T& lhs, const T& rhs) const
    {
        return lhs - rhs;
    }
};

template <>
struct minus<void> {
    template <typename T, typename U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
    {
        return wt::forward<T>(lhs) - wt::forward<U>(rhs);
    }
};

template <typename T = void>
struct multiplies {
    constexpr T operator()(const T& lhs, const T& rhs) const
    {
        return lhs * rhs;
    }
};

template <>
struct multiplies<void> {
    template <typename T, typename U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
    {
        return wt::forward<T>(lhs) * wt::forward<U>(rhs);
    }
};

template <typename T = void>
struct divides {
    constexpr T operator()(const T& lhs, const T& rhs) const
    {
        return lhs / rhs;
    }
};

template <>
struct divides<void> {
    template <typename T, typename U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
    {
        return wt::forward<T>(lhs) / wt::forward<U>(rhs);
    }
};

template <typename T = void>
struct modulus {
    constexpr T operator()(const T& lhs, const T& rhs) const
    {
        return lhs % rhs;
    }
};

template <>
struct modulus<void> {
    template <typename T, typename U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
    {
        return wt::forward<T>(lhs) % wt::forward<U>(rhs);
    }
};

template <typename T = void>
struct negate {
    constexpr T operator()(const T& _value) const
    {
        return -_value;
    }
};

template <>
struct negate<void> {
    template <typename T>
    constexpr auto operator()(T&& _value) const
    {
        return -wt::forward<T>(_value);
    }
};

/**
 *  Comparisons
 */
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
struct greater_equal {
    constexpr bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs >= rhs;
    }
};

template <>
struct greater_equal<void> {
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

/**
 *  Logical Operations
 */
template <typename T = void>
struct logical_and {
    constexpr bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs && rhs;
    }
};

template <>
struct logical_and<void> {
    template <typename T, typename U>
    constexpr bool operator()(T&& lhs, U&& rhs) const
    {
        return wt::forward<T>(lhs) && wt::forward<U>(rhs);
    }
};

template <typename T = void>
struct logical_or {
    constexpr bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs || rhs;
    }
};

template <>
struct logical_or<void> {
    template <typename T, typename U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
    {
        return wt::forward<T>(lhs) || wt::forward<U>(rhs);
    }
};

template <typename T = void>
struct logical_not {
    constexpr bool operator()(const T& _value) const
    {
        return !_value;
    }
};

template <>
struct logical_not<void> {
    template <typename T>
    constexpr auto operator()(T&& _value) const
    {
        return !wt::forward<T>(_value);
    }
};

/**
 *  Bitwise Operations
 */
template <typename T = void>
struct bit_and {
    constexpr T operator()(const T& lhs, const T& rhs) const
    {
        return lhs & rhs;
    }
};

template <>
struct bit_and<void> {
    template <typename T, typename U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
    {
        return wt::forward<T>(lhs) & wt::forward<U>(rhs);
    }
};

template <typename T = void>
struct bit_or {
    constexpr T operator()(const T& lhs, const T& rhs) const
    {
        return lhs | rhs;
    }
};

template <>
struct bit_or<void> {
    template <typename T, typename U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
    {
        return wt::forward<T>(lhs) | wt::forward<U>(rhs);
    }
};

template <typename T = void>
struct bit_xor {
    constexpr T operator()(const T& lhs, const T& rhs) const
    {
        return lhs ^ rhs;
    }
};

template <>
struct bit_xor<void> {
    template <typename T, typename U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
    {
        return wt::forward<T>(lhs) ^ wt::forward<U>(rhs);
    }
};

template <typename T = void>
struct bit_not {
    constexpr T operator()(const T& _value) const
    {
        return ~_value;
    }
};

template <>
struct bit_not<void> {
    template <typename T>
    constexpr auto operator()(T&& _value) const
    {
        return ~wt::forward<T>(_value);
    }
};

/**
 *  Default Ordering
 */
template <typename T>
struct default_order {
    typedef wt::less<T> type;
};

template <typename T>
using default_order_t = typename wt::default_order<T>::type;






} // namespace wt

#endif