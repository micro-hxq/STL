#ifndef _STL_WT_ALGORITHM_HPP_
#define _STL_WT_ALGORITHM_HPP_

namespace wt{

///////////////////////////////////////
// non-modifying sequence oeprations //
///////////////////////////////////////

//  all_of
//  any_of
//  none_of
template <typename InputIterator, typename UnaryPredicate>
bool
all_of(InputIterator _first, InputIterator _last, UnaryPredicate _pred)
{
    for(; _first != _last; ++_first)
    {
      if(!_pred(*_first))
        return false;
    }
    return true;
}

template <typename InputIterator, typename UnaryPredicate>
bool
any_of(InputIterator _first, InputIterator _last, UnaryPredicate _pred)
{
    for(; _first != _last; ++_first)
    {
      if(_pred(*_first))
        return true;
    }
    return false;
}

template <typename InputIterator, typename UnaryPredicate>
inline bool 
none_of(InputIterator _first, InputIterator _last, UnaryPredicate _pred)
{
    return !wt::any_of(_first, _last, _pred);
}

//  for_each
//  for_each_n
template <typename InputIterator, typename UnaryPredicate>
UnaryPredicate 
for_each(InputIterator _first, InputIterator _last, UnaryPredicate _pred)
{
    for(; _first != _last; ++_first)
        _pred(*_first);
    return wt::move(_pred);
}

template <typename InputIterator, typename Size, typename UnaryPredicate>
InputIterator
for_each_n(InputIterator _first, Size _n, UnaryPredicate _pred)
{
    for(Size i = 0; i < _n; ++i, ++_first)
        _pred(*_first);
    return _first;
}

//  count
//  count_if
template <typename InputIterator, typename T>
typename wt::iterator_traits<InputIterator>::difference_type
count(InputIterator _first, InputIterator _last, const T& _value)
{
    typename wt::iterator_traits<InputIterator>::difference_type result = 0;
    for(; _first != _last; ++_first)
    {
        if(*_first == _value)
            ++result;
    }
    return result;
}

template <typename InputIterator, typename UnaryPredicate>
typename wt::iterator_traits<InputIterator>::difference_type
count_if(InputIterator _first, InputIterator _last, UnaryPredicate _pred)
{
    typename wt::iterator_traits<InputIterator>::difference_type result = 0;
    for(; _first != _last; ++_first)
    {
        if(_pred(*_first))
            ++result;
    }
    return result;
}

//  mismatch
template <typename InputIterator1, typename InputIterator2>
wt::pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 _first1, InputIterator1 _last1, InputIterator2 _first2)
{
    for(; _first1 != _last1 && *_first1 == *_first2; ++_first1, ++_first2)
        ;
    return wt::make_pair(_first1, _first2);
}

template <typename InputIterator1, typename InputIterator2,
          typename BinaryPredicate>
wt::pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 _first1, InputIterator1 _last1, InputIterator2 _first2,
         BinaryPredicate _pred)
{
    for(; _first1 != _last1 && _pred(*_first1, *_first2); ++_first1, ++_first2)
        ;
    return wt::make_pair(_first1, _first2);
}

template <typename InputIterator1, typename InputIterator2>
wt::pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 _first1, InputIterator1 _last1,
         InputIterator2 _first2, InputIterator2 _last2)
{
    for(; _first1 != _last1 && _first2 != _last2 && *_first1 == *_first2;
        ++_first1, ++_first2)
        ;
    return wt::make_pair(_first1, _first2);
}

template <typename InputIterator1, typename InputIterator2,
          typename BinaryPredicate>
wt::pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 _first1, InputIterator1 _last1, InputIterator2 _first2,
         InputIterator2 _last2, BinaryPredicate _pred)
{
    for(; _first1 != _last1 && _first2 != _last2 && _pred(*_first1, *_first2);
        ++_first1, ++_first2)
        ;
    return wt::make_pair(_first1, _first2);
}

//  adjacent_find
//  find
//  find_if
//  find_if_not
//  find_first_of
template <typename ForwardIterator>
ForwardIterator 
adjacent_find(ForwardIterator _first, ForwardIterator _last)
{
    if(_first == _last)
        return _last;
    ForwardIterator next = _first;
    ++next;
    for(; next != _last; ++_first, ++next)
    {
        if(*_first == *next)
            return _first;
    }
    return _last;
}

template <typename ForwardIterator, typename BinaryPredicate>
ForwardIterator
adjacent_find(ForwardIterator _first, ForwardIterator _last,
              BinaryPredicate _pred)
{
    if(_first == _last)
        return _last;
    ForwardIterator next = _first;
    ++next;
    for(; next != _last; ++_first, ++next)
    {
        if(_pred(*_first, *next))
            return _first;
    }
    return next;
}

template <typename InputIterator, typename T>
InputIterator find(InputIterator _first, InputIterator _last, const T& _value)
{
    for(; _first != _last; ++_first)
    {
        if(*_first == _value)
            return _first;
    }
    return _last;
}

template <typename InputIterator, typename UnaryPredicate>
InputIterator find_if(InputIterator _first, InputIterator _last,
                      UnaryPredicate _pred)
{
    for(; _first != _last; ++_first)
    {
        if(_pred(*_first))
            return _first;
    }
    return _last;
}

template <typename InputIterator, typename UnaryPredicate>
InputIterator find_if_not(InputIterator _first, InputIterator _last,
                          UnaryPredicate _pred)
{
    for(; _first != _last; ++_first)
    {
        if(!_pred(*_first))
            return _first;
    }
    return _last;
}

template <typename InputIterator, typename ForwardIterator>
InputIterator find_first_of(InputIterator _first, InputIterator _last,
                            ForwardIterator _s_first, ForwardIterator _s_last)
{
    for(; _first != _last; ++_first)
    {
        for(auto iter = _s_first; iter != _s_first; ++iter)
        {
            if(*_first == *iter)
                return _first;
        }
    }
    return _last;
}

template <typename InputIterator, typename ForwardIterator,
          typename BinaryPredicate>
InputIterator find_first_of(InputIterator _first, InputIterator _last,
                            ForwardIterator _s_first, ForwardIterator _s_last,
                            BinaryPredicate _pred)
{
    for(; _first != _last; ++_first)
    {
        for(auto iter = _s_first; iter != _s_last; ++iter)
        {
            if(_pred(*_first, *iter))
                return _first;
        }
    }
    return _last;
}

//  search
//  search_n
template <typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator1 search(ForwardIterator1 _first, ForwardIterator1 _last,
                        ForwardIterator2 _s_first, ForwardIterator2 _s_last)
{
    if(_first == _last || _s_first == _s_last)
        return _last;
    ForwardIterator2 temp = _s_first;
    ++temp;
    if(temp == _s_last)
        return wt::find(_first, _last, *_s_first);

    ForwardIterator1 iter_end = _last - wt::distance(_s_first, _s_last) + 1;
    for(; _first != iter_end; ++_first)
    {
        ForwardIterator1 it1 = _first;
        for(ForwardIterator2 it2 = _s_first; ; ++it1, ++it2)
        {
            if(it2 == _s_last)
                return _first;
            if(!(*it1 == *it2))
                break;
        }
    }
    return _last;
}

template <typename ForwardIterator1, typename ForwardIterator2,
          typename BinaryPredicate>
ForwardIterator1 search(ForwardIterator1 _first, ForwardIterator1 _last,
                        ForwardIterator2 _s_first, ForwardIterator2 _s_last,
                        BinaryPredicate _pred)
{
    if(_first == _last || _s_first == _s_last)
        return _last;
    ForwardIterator2 temp = _s_first;
    ++temp;
    if(temp == _s_last)
    {
        while(_first != _last && !_pred(*_first, *_s_first))
            ++_first;
        return _first;
    }
    ForwardIterator1 iter_end = _last - wt::distance(_s_first, _s_last) + 1;
    for(; _first != iter_end; ++_first)
    {
        ForwardIterator1 it1 = _first;
        for(ForwardIterator2 it2 = _s_first; ; ++it1, ++it2)
        {
            if(it2 == _s_last)
                return _first;
            if(!_pred(*it1, *it2))
                break;
        }
    }
    return _last;
}

template <typename ForwardIterator, typename Size, typename T>
ForwardIterator
search_n(ForwardIterator _first, ForwardIterator _last,
         Size _n, const T& _value)
{
    if(_first == _last || _n == 0)
        return _first;

    for(; _first != _last; ++_first)
    {
        if(*_first == _value)
        {
            ForwardIterator result = _first;
            Size left = _n;
            while(true)
            {
                --left;
                if(left == 0)
                    return result;

                ++_first;
                if(_first == _last)
                    return _last;
                if(*_first != _value)
                    break;
            }
        }
    }
    return _last;
}

template <typename ForwardIterator, typename Size, typename T,
          typename BinaryPredicate>
ForwardIterator
search_n(ForwardIterator _first, ForwardIterator _last,
         Size _n, const T& _value, BinaryPredicate _pred)
{
    if(_first == _last || _n == 0)
        return _first;

    for(; _first != _last; ++_first)
    {
        if(_pred(*_first, _value))
        {
            ForwardIterator result = _first;
            Size left = _n;
            while(true)
            {
                --left;
                if(left == 0)
                    return result;

                ++_first;
                if(_first == _last)
                    return _last;
                if(!_pred(*_first, _value))
                    break;
            }
        }
    }
    return _last;
}

//  find_end
template <typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator1 
_find_end_dispatch(ForwardIterator1 _first, ForwardIterator1 _last,
                   ForwardIterator2 _s_first, ForwardIterator2 _s_last,
                   forward_iterator_tag, forward_iterator_tag)
{
    if(_s_first == _s_last)
        return _last;
    ForwardIterator1 result = _last;
    while(true)
    {
        ForwardIterator1 new_result = wt::search(_first, _last, _s_first, _s_last);
        if(new_result == _last)
        {
            break;
        }
        else
        {
            result = new_result;
            _first = new_result + 1;
        }
    }
    return result;
}

template <typename BidirectionalIterator1, typename BidirectionalIterator2>
BidirectionalIterator1
_find_end_dispatch(BidirectionalIterator1 _first, BidirectionalIterator1 _last,
                   BidirectionalIterator2 _s_first, BidirectionalIterator2 _s_last,
                   bidirectional_iterator_tag, bidirectional_iterator_tag)
{
    if(_s_first == _s_last)
        return _last;
    auto reverse_last = wt::make_reverse_iterator(_first);
    auto rresult = wt::search(wt::make_reverse_iterator(_last),
                              reverse_last,
                              wt::make_reverse_iterator(_s_last),
                              wt::make_reverse_iterator(_s_first));
    if(rresult == reverse_last)
        return _last;
    BidirectionalIterator1 result = rresult.base();
    wt::advance(result, -wt::distance(_s_first, _s_last));
    return result;
}

template <typename ForwardIterator1, typename ForwardIterator2,
          typename BinaryPredicate>
ForwardIterator1 
_find_end_dispatch(ForwardIterator1 _first, ForwardIterator1 _last,
                   ForwardIterator2 _s_first, ForwardIterator2 _s_last,
                   BinaryPredicate _pred, forward_iterator_tag,
                   forward_iterator_tag)
{
    if(_s_first == _s_last)
        return _last;
    ForwardIterator1 result = _last;
    while(true)
    {
        ForwardIterator1 new_result = wt::search(_first, _last,
                                                 _s_first, _s_last,
                                                 _pred);
        if(new_result == _last)
        {
            break;
        }
        else
        {
            result = new_result;
            _first = new_result + 1;
        }
    }
    return result;
}

template <typename BidirectionalIterator1, typename BidirectionalIterator2,
          typename BinaryPredicate>
BidirectionalIterator1
_find_end_dispatch(BidirectionalIterator1 _first, BidirectionalIterator1 _last,
                   BidirectionalIterator2 _s_first, BidirectionalIterator2 _s_last,
                   BinaryPredicate _pred, bidirectional_iterator_tag,
                   bidirectional_iterator_tag)
{
    if(_s_first == _s_last)
        return _last;
    auto reverse_last = wt::make_reverse_iterator(_first);
    auto rresult = wt::search(wt::make_reverse_iterator(_last),
                              reverse_last,
                              wt::make_reverse_iterator(_s_last),
                              wt::make_reverse_iterator(_s_first),
                              _pred);
    if(rresult == reverse_last)
        return _last;
    BidirectionalIterator1 result = rresult.base();
    wt::advance(result, -wt::distance(_s_first, _s_last));
    return result;
}

template <typename ForwardIterator1, typename ForwardIterator2>
inline ForwardIterator1 
find_end(ForwardIterator1 _first, ForwardIterator1 _last,
         ForwardIterator2 _s_first, ForwardIterator2 _s_last)
{
    return wt::_find_end_dispatch(_first, _last, _s_first, _s_last,
                                  _ITERATOR_CATEGORY(_first),
                                  _ITERATOR_CATEGORY(_s_first));
}
template <typename ForwardIterator1, typename ForwardIterator2,
          typename BinaryPredicate>
inline ForwardIterator1 
find_end(ForwardIterator1 _first, ForwardIterator1 _last,
         ForwardIterator2 _s_first, ForwardIterator2 _s_last,
         BinaryPredicate _pred)
{
    return wt::_find_end_dispatch(_first, _last, _s_first, _s_last, _pred,
                                  _ITERATOR_CATEGORY(_first),
                                  _ITERATOR_CATEGORY(_s_first));
}




///////////////////////////////////
// Modifying Sequence Operations //
///////////////////////////////////

//  swap_ranges
//  swap 
template <typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator2 
swap_ranges(ForwardIterator1 _first1, ForwardIterator1 _last1,
            ForwardIterator2 _first2)
{
    for(; _first1 != _last1; ++_first1, ++_first2)
      wt::iter_swap(_first1, _first2);
    return _first2;
}

template <typename T, std::size_t N>
inline void swap(T (&_a)[N], T (&_b)[N])
{
    wt::swap_ranges(_a, _a + N, _b);
}

//  copy_if
template <typename InputIterator, typename OutputIterator, 
          typename UnaryPredicate>
OutputIterator
copy_if(InputIterator _first, InputIterator _last, OutputIterator _dest,
        UnaryPredicate _pred)
{
    for(; _first != _last; ++_first)
    {
        if(_pred(*_first))
            *_dest++ = *_first;
    }
    return _dest;
}

//  move
//  move_backward
template <typename InputIterator, typename OutputIterator>
OutputIterator
move(InputIterator _first, InputIterator _last, OutputIterator _dest)
{
    for(; _first != _last; ++_first)
        *_dest++ = wt::move(*_first);
    return _dest;
}

template <typename BidirectionalIterator1, typename BidirectionalIterator2>
BidirectionalIterator2
move_backward(BidirectionalIterator1 _first, BidirectionalIterator1 _last,
              BidirectionalIterator2 _dest)
{
    while(_first != _last)
    {
        *(--_dest) = wt::move(*(--_last));
    }
    return _dest;
}

//  transform
template <typename InputIterator, typename OutputIterator,
          typename UnaryPredicate>
OutputIterator
transform(InputIterator _first, InputIterator _last, OutputIterator _dest,
          UnaryPredicate _pred)
{
    for(; _first != _last; ++_first)
    {
        *_dest++ = _pred(*_first);
    }
    return _dest;
}

template <typename InputIterator1, typename InputIterator2,
          typename OutputIterator, typename BinaryPredicate>
OutputIterator
transform(InputIterator1 _first1, InputIterator1 _last1, InputIterator2 _first2,
          OutputIterator _dest, BinaryPredicate _pred)
{
    for(; _first1 != _last1; ++_first1)
    {
        *_dest++ = _pred(*_first1, *_first2);
    }
    return _dest;
}

//  generate
//  generate_n
template <typename ForwardIterator, typename Generator>
void
generate(ForwardIterator _first, ForwardIterator _last, Generator _g)
{
    for(; _first != _last; ++_first)
        *_first = _g();
}

template <typename OutputIterator, typename Size, typename Generator>
OutputIterator
generate_n(OutputIterator _first, Size _n, Generator _g)
{
    for(Size i = 0; i < _n; ++i)
        *_first++ = _g();
    return _first;
}

//  remove_copy
//  remove_copy_if
//  remove
//  remove_if
template <typename InputIterator, typename OutputIterator, typename T>
OutputIterator
remove_copy(InputIterator _first, InputIterator _last, OutputIterator _dest,
            const T& _value)
{
    for(; _first != _last; ++_first)
    {
        if(!(*_first == _value))
            *_dest++ = *_first;
    }
    return _dest;
}

template <typename InputIterator, typename OutputIterator,
          typename UnaryPredicate>
OutputIterator 
remove_copy_if(InputIterator _first, InputIterator _last, OutputIterator _dest,
               UnaryPredicate _pred)
{
    for(; _first != _last; ++_first)
    {
        if(!_pred(*_first))
            *_dest++ = *_first;
    }
    return _dest;
}

template <typename ForwardIterator, typename T>
ForwardIterator
remove(ForwardIterator _first, ForwardIterator _last, const T& _value)
{
    _first = wt::find(_first, _last, _value);
    ForwardIterator next = _first;
    return _first == _last ? _last 
        : wt::remove_copy(++next, _last, _first, _value);
}

template <typename ForwardIterator, typename UnaryPredicate>
ForwardIterator
remove_if(ForwardIterator _first, ForwardIterator _last, UnaryPredicate _pred)
{
    _first = wt::find_if(_first, _last, _pred);
    ForwardIterator next = _first;
    return _first == _last ? _last
        : wt::remove_copy_if(++next, _last, _first, _pred);
}

//  replace
//  replace_if
//  replace_copy
//  replace_copy_if
template <typename ForwardIterator, typename T>
void
replace(ForwardIterator _first, ForwardIterator _last, const T& _old,
        const T& _new)
{
    for(; _first != _last; ++_first)
    {
        if(*_first == _old)
            *_first = _new;
    }
}

template <typename ForwardIterator, typename UnaryPredicate, typename T>
void replace_if(ForwardIterator _first, ForwardIterator _last,
                UnaryPredicate _pred, const T& _new)
{
    for(; _first != _last; ++_first)
    {
        if(_pred(*_first))
            *_first = _new;
    }
}

template <typename InputIterator, typename OutputIterator, typename T>
OutputIterator
replace_copy(InputIterator _first, InputIterator _last, OutputIterator _dest,
             const T& _old, const T& _new)
{
    for(; _first != _last; ++_first)
        *_dest++ = (*_first == _old) ? _new : _old;
    return _dest;
}

template <typename InputIterator, typename OutputIterator,
          typename UnaryPredicate, typename T>
OutputIterator
replace_copy_if(InputIterator _first, InputIterator _last, OutputIterator _dest,
                UnaryPredicate _pred, const T& _new)
{
    for(; _first != _last; ++_first)
        *_dest++ = _pred(*_first) ? _new : *_first;
    return _dest;
}

//  reverse
//  reverse_copy
template <typename BidirectionalIterator>
void
reverse(BidirectionalIterator _first, BidirectionalIterator _last)
{
    for(; _first != _last && _first != --_last; ++_first)
        wt::iter_swap(_first, _last);
}

template <typename BidirectionalIterator, typename OutputIterator>
OutputIterator
reverse_copy(BidirectionalIterator _first, BidirectionalIterator _last,
             OutputIterator _dest)
{
    while(_first != _last)
        *_dest++ = *(--_last);
    return _dest;
}

//  rotate
//  rotate_copy
template <typename ForwardIterator>
ForwardIterator
rotate(ForwardIterator _first, ForwardIterator _n_first, ForwardIterator _last)
{
    const auto offset = wt::distance(_n_first, _last);
    ForwardIterator old_first = _first;
    ForwardIterator next = _n_first;
    while(_first != next)
    {
        wt::iter_swap(_first++, next++);
        if(next == _last)
            next = _n_first;
        if(_first == _n_first)
            _n_first = next;
    }
    wt::advance(old_first, offset);
    return old_first;
}

template <typename ForwardIterator, typename OutputIterator>
OutputIterator
rotate_copy(ForwardIterator _first, ForwardIterator _n_first,
            ForwardIterator _last, OutputIterator _dest)
{
    _dest = wt::copy(_n_first, _last, _dest);
    return wt::copy(_first, _n_first, _dest);
}

//  unique
//  unique_copy
template <typename ForwardIterator>
ForwardIterator
unique(ForwardIterator _first, ForwardIterator _last)
{
    if(_first == _last)
        return _last;
    ForwardIterator next = _first;
    while(++next != _last)
    {
        if(*_first != *next && ++_first != next)
            *_first = wt::move(*next);
    }
    return ++_first;
}

template <typename ForwardIterator, typename BinaryPredicate>
ForwardIterator
unique(ForwardIterator _first, ForwardIterator _last, BinaryPredicate _pred)
{
    if(_first == _last)
        return _last;
    ForwardIterator next = _first;
    while(++next != _last)
    {
        if(!_pred(*_first, *next) && ++_first != next)
            *_first = wt::move(*next);
    }
    return ++_first;
}

template <typename InputIterator, typename OutputIterator>
OutputIterator
_unique_copy_dispatch(InputIterator _first, InputIterator _last,
                      OutputIterator _dest, wt::output_iterator_tag)
{
    auto value = *_first;
    ++_first;
    for(; _first != _last; ++_first)
    {
        if(*_first != value)
        {
            *_dest++ = wt::move(value);
            value = *_first;
        }
    }
    *_dest++ = wt::move(value);
    return _dest;
}

template <typename InputIterator, typename ForwardIterator>
ForwardIterator
_unique_copy_dispatch(InputIterator _first, InputIterator _last,
                      ForwardIterator _dest, wt::forward_iterator_tag)
{
    for(*_dest = *_first++; _first != _last; ++_first)
    {
        if(*_first != *_dest)
            *(++_dest) = *_first;
    }
    return ++_dest;
}

template <typename InputIterator, typename OutputIterator>
inline OutputIterator
unique_copy(InputIterator _first, InputIterator _last, OutputIterator _dest)
{
    return _first == _last ? _dest : wt::_unique_copy_dispatch(_first, _last,
                                         _dest, _ITERATOR_CATEGORY(_dest));
}

template <typename InputIterator, typename OutputIterator,
          typename BinaryPredicate>
OutputIterator
_unique_copy_dispatch(InputIterator _first, InputIterator _last,
                      OutputIterator _dest, BinaryPredicate _pred,
                      wt::output_iterator_tag)
{
    auto value = *_first;
    ++_first;
    for(; _first != _last; ++_first)
    {
        if(!_pred(*_first, value))
        {
            *_dest++ = wt::move(value);
            value = *_first;
        }
    }
    *_dest++ = wt::move(value);
    return _dest; 
}

template <typename InputIterator, typename ForwardIterator,
          typename BinaryPredicate>
ForwardIterator
_unique_copy_dispatch(InputIterator _first, InputIterator _last,
                      ForwardIterator _dest, BinaryPredicate _pred,
                      wt::forward_iterator_tag)
{
    for(*_dest = *_first++; _first != _last; ++_first)
    {
        if(!_pred(*_dest, *_first))
            *(++_dest) = *_first;
    }
    return ++_dest;
}

template <typename InputIterator, typename OutputIterator,
          typename BinaryPredicate>
inline OutputIterator
unique_copy(InputIterator _first, InputIterator _last,
            OutputIterator _dest, BinaryPredicate _pred)
{
    return _first == _last ? _dest : wt::_unique_copy_dispatch(_first, _last,
                                    _dest, _pred, _ITERATOR_CATEGORY(_dest));
}






} // namespace wt
#endif