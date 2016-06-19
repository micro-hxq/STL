#ifndef _STL_WT_RELOPS_HPP_
#define _STL_WT_RELOPS_HPP_

namespace wt{

namespace rel_ops{

template <typename T>
inline bool operator!=(const T& lhs, const T& rhs)
{
    return !(lhs == rhs);
}

template <typename T>
inline bool operator>(const T& lhs, const T& rhs)
{
    return rhs < lhs;
}

template <typename T>
inline bool operator<=(const T& lhs, const T& rhs)
{
    return !(rhs < lhs);
}

template <typename T>
inline bool operator>=(const T& lhs, const T& rhs)
{
    return !(lhs < rhs);
}

} // namespace rel_ops

} // namespace wt

#endif