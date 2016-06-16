#ifndef _WT_UTILITY_HPP_
#define _WT_UTILITY_HPP_

#include "type_traits.hpp"

namespace wt{

template <typename T>
constexpr T&& forward(wt::remove_reference_t<T>& t) noexcept
{
    return static_cast<T&&>(t);
}

template <typename T>
constexpr T&& forward(wt::remove_reference_t<T>&& t) noexcept
{
    return static_cast<T&&>(t);
}






} // namespace wt

#endif