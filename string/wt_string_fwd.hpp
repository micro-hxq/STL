#ifndef _STL_WT_STRING_FWD_HPP_
#define _STL_WT_STRING_FWD_HPP_

namespace wt {

template <typename CharT, 
          typename Traits = char_traits<CharT>,
          typename Allocator = allocator<CharT>>
class basic_string;

typedef basic_string<char>      string;
typedef basic_string<wchar_t>   wstring;

// static const char* get_c_string(const string&);

} // namespace wt

#endif