#ifndef _STL_WT_CHAR_TRAITS_HPP_
#define _STL_WT_CHAR_TRAITS_HPP_

/**
 *  depend on:
 *            <string.h>            
 *            <wchar.h>
 */


namespace wt {

template <typename CharT, typename IntT>
class _char_traits_base {
public:
    typedef CharT   char_type;
    typedef IntT    int_type;

    // TODO: streamoff streampos mbstate_t
    
    static void assign(char_type& _c1, const char_type& _c2) noexcept
    {
        _c1 = _c2;
    }

    static constexpr bool eq(char_type _c1, char_type _c2) noexcept
    {
        return _c1 == _c2;
    }

    static constexpr bool lt(char_type _c1, char_type _c2) noexcept
    {
        return _c1 < _c2;
    }

    static int compare(const char_type* _s1, const char_type* _s2, size_t _n)
    {
        for(size_t index = 0; index < _n; ++index)
        {
            if(!eq(_s1[index], _s2[index]))
                return _s1[index] < _s2[index] ? -1 : 1;
        }
        return 0;
    }

    static size_t length(const char_type* _s) noexcept
    {
        const char_type null_char = char_type();
        size_t i = 0;
        for(; !eq(_s[i], null_char); ++i) {}
        return i;
    }

    static const char_type* find(const char_type* _s, size_t _n, const char_type& _c)
    {
        for(; _n > 0; --_n, ++_s)
        {
            if(eq(*_s, _c))
                return _s;
        }
        return nullptr;
    }

    static char_type* move(char_type* _s1, const char_type* _s2, size_t _n)
    {
        memmove(_s1, _s2, _n * sizeof(char_type));
        return _s1;
    }

    static char_type* copy(char_type* _s1, const char_type* _s2, size_t _n)
    {
        memcpy(_s1, _s2, _n * sizeof(char_type));
        return _s1;
    }

    static char_type* assign(char_type* _s, size_t _n, char_type _c)
    {
        for(size_t i = 0; i < _n; ++i)
            _s[i] = _c;
        return _s;
    }

    static constexpr char_type to_char_type(int_type _c) noexcept
    {
        return static_cast<char_type>(_c);
    }

    static constexpr int_type to_int_type(char_type _c) noexcept
    {
        return static_cast<int_type>(_c);
    }

    static constexpr bool eq_int_type(int_type _c1, int_type _c2) noexcept
    {
        return _c1 == _c2;
    }

    static constexpr int_type eof() noexcept
    {
        return static_cast<int_type>(-1);
    }

    static constexpr int_type not_eof(int_type _c) noexcept
    {
        return eq_int_type(_c, eof()) ? 0 : _c;
    }

};

////////////////////////////
// generic char_traits    //
// only work for POD type //
////////////////////////////
template <typename CharT>
class char_traits : public _char_traits_base<CharT, CharT> {};

template <>
class char_traits<char> : public  _char_traits_base<char, int> {
public:
    static int compare(const char* _s1, const char* _s2, size_t _n)
    {
        return memcmp(_s1, _s2, _n);
    }

    static size_t length(const char* _s)
    {
        return strlen(_s);
    }

    static void assign(char& _c, char _c2)
    {
        _c = _c2;
    }

    static char* assign(char* _s, size_t _n, char _c)
    {
        memset(_s, _c, _n);
        return _s;
    }

    static char_type to_char_type(int _c)
    {
        return static_cast<char_type>(static_cast<unsigned char>(_c));
    }

    static int to_int_type(char _c)
    {
        return static_cast<int>(static_cast<unsigned char>(_c));
    }
};

template <>
class char_traits<wchar_t> : public _char_traits_base<wchar_t, int> {};

} // namespace wt


#endif