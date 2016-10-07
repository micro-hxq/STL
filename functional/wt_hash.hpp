#ifndef _STL_WT_HASH_VALUE_HPP_
#define _STL_WT_HASH_VALUE_HPP_

namespace wt {

template <typename T>
struct hash { };


#define WT_HAS_TRIVIAL_HASH(_Tp)                    \
template<>                                          \
struct hash<_Tp> {                                  \
    std::size_t operator()(_Tp _key) const noexcept \
    {   return static_cast<std::size_t>(_key);  }   \
};                                                  \

//  return itself if tpye is integer
WT_HAS_TRIVIAL_HASH(bool)
WT_HAS_TRIVIAL_HASH(char)
WT_HAS_TRIVIAL_HASH(signed char)
WT_HAS_TRIVIAL_HASH(unsigned char)
WT_HAS_TRIVIAL_HASH(char16_t)
WT_HAS_TRIVIAL_HASH(char32_t)
WT_HAS_TRIVIAL_HASH(wchar_t)
WT_HAS_TRIVIAL_HASH(unsigned short)
WT_HAS_TRIVIAL_HASH(short)
WT_HAS_TRIVIAL_HASH(unsigned int)
WT_HAS_TRIVIAL_HASH(int)
WT_HAS_TRIVIAL_HASH(unsigned long)
WT_HAS_TRIVIAL_HASH(long)
WT_HAS_TRIVIAL_HASH(unsigned long long)
WT_HAS_TRIVIAL_HASH(long long)

template <typename T>
struct hash<T*> {
    std::size_t operator()(T* _addr) const noexcept
    {
        return reinterpret_cast<std::size_t>(_addr);
    }
};

//  TODO: float hash
//  TODO: double hash
//  TODO: long double hash
//  TODO: string hash

} // namespace wt

#endif