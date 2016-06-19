#ifndef _STL_WT_PAIR_HPP_
#define _STL_WT_PAIR_HPP_ 

namespace wt{

template <typename T1, typename T2>
struct pair {
    typedef T1      first_type;
    typedef T2      second_type;

    T1  first;
    T2  second;

    pair() : first(T1()), second(T2()) {}
    pair(const T1& t1, const T2& t2) : first(t1), second(t2) {}

    template <typename U, typename V>
    pair(const pair<U,V>& other) : first(other.first), second(other.second) {}
};


template <typename T1, typename T2>
inline bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <typename T1, typename T2>
inline bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{
    return !(lhs == rhs);
}

template <typename T1, typename T2>
inline bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{
    return lhs.first < rhs.first ||
           (!(rhs.first < lhs.first) && lhs.second < rhs.second); 
}

template <typename T1, typename T2>
inline bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{
    return !(rhs < lhs);
}

template <typename T1, typename T2>
inline bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{
    return rhs < lhs;
}

template <typename T1, typename T2>
inline bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{
    return !(lhs < rhs);
}


template <typename T1, typename T2>
pair<T1,T2> make_pair(const T1& a,const T2& b)
{
    return pair<T1,T2>(a,b);
}

} // namespace wt


#endif