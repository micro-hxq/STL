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

//////////////////////////////
//  Partitioning Operations //
//////////////////////////////

//  partition
//  partition_copy
template <typename ForwardIterator, typename UnaryPredicate>
ForwardIterator
_partition_dispatch(ForwardIterator _first, ForwardIterator _last,
                    UnaryPredicate _pred, wt::forward_iterator_tag)
{
    _first = wt::find_if_not(_first, _last, _pred);
    if(_first == _last)
        return _last;
    ForwardIterator next = _first;
    while(++next != _last)
    {
        if(_pred(*next))
            wt::iter_swap(_first++, next);
    }
    return _first;
}

template <typename BidirectionalIterator, typename UnaryPredicate>
BidirectionalIterator
_partition_dispatch(BidirectionalIterator _first, BidirectionalIterator _last,
                    UnaryPredicate _pred, wt::bidirectional_iterator_tag)
{
    if(_first == _last)
        return _last;
    --_last;
    while(true)
    {
        while(_first != _last && _pred(*_first))
            ++_first;
        while(_first != _last && !_pred(*_last))
            --_last;
        if(_first != _last)
            wt::iter_swap(_first, _last);
        else
            break;
    }
    return _first;
}

template <typename ForwardIterator, typename UnaryPredicate>
inline ForwardIterator
partition(ForwardIterator _first, ForwardIterator _last, UnaryPredicate _pred)
{
    return wt::_partition_dispatch(_first, _last, _pred, 
                                   _ITERATOR_CATEGORY(_first));
}

template <typename InputIterator, typename OutputIterator1, 
          typename OutputIterator2, typename UnaryPredicate>
wt::pair<OutputIterator1, OutputIterator2>
partition_copy(InputIterator _first, InputIterator _last,
               OutputIterator1 _dest_true, OutputIterator2 _dest_false,
               UnaryPredicate _pred)
{
    for(; _first != _last; ++_first)
    {
        if(_pred(*_first))
            *_dest_true++  = *_first;
        else
            *_dest_false++ = *_first;
    }
    return wt::make_pair(_dest_true, _dest_false);
}

//  is_partitioned
template <typename InputIterator, typename UnaryPredicate>
bool
is_partitioned(InputIterator _first, InputIterator _last, UnaryPredicate _pred)
{
    while(_first != _last && _pred(*_first))
        ++_first;
    while(_first != _last && !_pred(*_first))
        ++_first;
    return _first == _last;
}
//  partition_point
// template <typename ForwardIterator, typename UnaryPredicate>
// ForwardIterator
// _partition_point_dispatch(ForwardIterator _first, ForwardIterator _last,
//                           UnaryPredicate _pred, wt::forward_iterator_tag)
// {
//     while(_first != _last && _pred(*_first))
//         ++_first;
//     return _first;
// }

// template <typename BidirectionalIterator, typename UnaryPredicate>
// BidirectionalIterator
// _partition_point_dispatch(BidirectionalIterator _first,
//                           BidirectionalIterator _last,
//                           UnaryPredicate _pred,
//                           wt::bidirectional_iterator_tag)
// {
//     if(_first == _last)
//         return _last;
//     while(true)
//     {
//         --_last;
//         if(!_pred(*_first))
//             return _first;
//         if(_pred(*_last))
//             return ++_last;
//         ++_first;
//     }
// }

// template <typename RandomAccessIterator, typename UnaryPredicate>
// RandomAccessIterator
// _partition_point_dispatch(RandomAccessIterator _first,
//                           RandomAccessIterator _last,
//                           UnaryPredicate _pred,
//                           wt::random_access_iterator_tag)
// {
//     RandomAccessIterator mid;
//     while(_first != _last)
//     {
//         mid = _first + wt::distance(_first, _last) / 2;
//         if(_pred(*mid))
//         {
//             if(++mid != _last && !_pred(*mid))
//                 return mid;
//             _first = mid;
//         }
//         else
//         {
//             if(mid != _first && _pred(*(--mid)))
//                 return ++mid;
//             _last = mid;
//         }
//     }
//     return _last;
// }

// template <typename ForwardIterator, typename UnaryPredicate>
// inline ForwardIterator
// partition_point(ForwardIterator _first, ForwardIterator _last,
//                 UnaryPredicate _pred)
// {
//     return wt::_partition_point_dispatch(_first, _last, _pred,
//                                          _ITERATOR_CATEGORY(_first));
// }
//  Time Complexity: log2(N)
template <typename ForwardIterator, typename UnaryPredicate>
ForwardIterator
partition_point(ForwardIterator _first, ForwardIterator _last,
                UnaryPredicate _pred)
{
    ForwardIterator mid;
    auto len = wt::distance(_first, _last);
    while(len > 0)
    {
        mid = _first;
        auto step = len / 2;
        wt::advance(mid, step);
        if(_pred(*mid))
        {
            _first = ++mid;
            len -= step + 1;
        }
        else
        {
            len = step;
        }
    }
    return _first;
}

//  two categories for stable_partition
struct less_time { };
struct less_space { };

//  Time Complexity: N
//  Space Complexity: <= 2 * N;
template <typename BidirectionalIterator, typename UnaryPredicate>
BidirectionalIterator
_stable_partition_dispatch(BidirectionalIterator _first, 
                           BidirectionalIterator _last,
                           UnaryPredicate _pred, wt::less_time)
{
    if(_first == _last)
        return _last;

    const auto N = wt::distance(_first, _last);

    typedef typename wt::iterator_traits<BidirectionalIterator>::value_type _Ty;
    _Ty* aux = new _Ty[N];
    std::size_t index = 0;

    BidirectionalIterator next = _first;
    for(; next != _last; ++next)
    {
        if(!_pred(*next))
            aux[index++] = wt::move(*next);
        else if(next != _first)
            *_first++ = wt::move(*next);
    }
    wt::move(aux, aux + index, _first);
    delete[] aux;

    return _first;
}

//  Time Complexity: NlogN
//  Space Complexity: N
template <typename BidirectionalIterator, typename UnaryPredicate>
BidirectionalIterator
_stable_partition_dispatch(BidirectionalIterator _first,
                           BidirectionalIterator _last,
                           UnaryPredicate _pred, wt::less_space)
{
    while(_first != _last && _pred(*_first))
        ++_first;

    if(_first == _last)
        return _last;

    BidirectionalIterator pivot;
    BidirectionalIterator next = _first;
    while(next != _last)
    {
        pivot = next;
        while(++pivot != _last && !_pred(*pivot))
            ;
        if(pivot == _last)
            return _first;

        next = pivot;
        while(++next != _last && _pred(*next))
            ;
        _first = wt::rotate(_first, pivot, next);
    }
    return _first;
}

template <typename BidirectionalIterator, typename UnaryPredicate,
          typename Policy = wt::less_time>
inline BidirectionalIterator
stable_partition(BidirectionalIterator _first, BidirectionalIterator _last,
                 UnaryPredicate _pred, Policy _p = Policy())
{
    return wt::_stable_partition_dispatch(_first, _last, _pred, _p);
}


////////////////////////
// Sorting Operations //
////////////////////////

//  is_sort_until
//  is_sort
template <typename ForwardIterator>
ForwardIterator
is_sort_until(ForwardIterator _first, ForwardIterator _last)
{
    if(_first == _last)
        return _last;

    ForwardIterator next = _first;
    while(++next != _last && !(*next < *_first))
        ++_first;
    return next;
}

template <typename ForwardIterator, typename Compare>
ForwardIterator
is_sort_until(ForwardIterator _first, ForwardIterator _last, Compare _comp)
{
    if(_first == _last)
        return _last;

    ForwardIterator next = _first;
    while(++next != _last && !_comp(*next, *_first))
        ++_first;
    return next;
}

template <typename ForwardIterator>
inline bool
is_sort(ForwardIterator _first, ForwardIterator _last)
{
    return wt::is_sort_until(_first, _last) == _last;
}

template <typename ForwardIterator, typename Compare>
inline bool
is_sort(ForwardIterator _first, ForwardIterator _last, Compare _comp)
{
    return wt::is_sort_until(_first, _last, _comp) == _last;
}

//  sort
//  TODO

//  partial_sort
//  partial_sort_copy
template <typename RandomAccessIterator>
void 
partial_sort(RandomAccessIterator _first, RandomAccessIterator _mid, 
             RandomAccessIterator _last)
{
    wt::make_heap(_first, _mid);

    for(RandomAccessIterator iter = _mid; iter < _last; ++iter)
    {
        if(*iter < *_first)
            wt::_pop_heap(_first, _mid, iter, _DIFFERENCE_TYPE(_first),
                          wt::move(*iter));
    }
    wt::sort_heap(_first, _mid);
}

template <typename RandomAccessIterator, typename Compare>
void
partial_sort(RandomAccessIterator _first, RandomAccessIterator _mid,
             RandomAccessIterator _last, Compare _comp)
{
    wt::make_heap(_first, _mid, _comp);

    for(RandomAccessIterator iter = _mid; iter < _last; ++iter)
    {
        if(_comp(*iter, *_first))
            wt::_pop_heap(_first, _mid, iter, _DIFFERENCE_TYPE(_first),
                          wt::move(*iter));
    }
    wt::sort_heap(_first, _mid, _comp);
}

template <typename InputIterator, typename RandomAccessIterator>
RandomAccessIterator
partial_sort_copy(InputIterator _first, InputIterator _last,
                  RandomAccessIterator _dest_f, RandomAccessIterator _dest_l)
{
    if(_dest_f == _dest_l)
        return _dest_l;

    RandomAccessIterator current = _dest_f;
    for(; _first != _last && current != _dest_l; ++_first, ++current)
        *current = *_first;

    wt::make_heap(_dest_f, current);
    for(; _first != _last; ++_first)
    {   
        if(*_first < *_dest_f)
            wt::_adjust_heap(_dest_f, decltype(_dest_f - _dest_l)(0),
                             wt::distance(_dest_f, current), *_first);
    }
    wt::sort_heap(_dest_f, current);
    return current;
}

template <typename InputIterator, typename RandomAccessIterator,
          typename Compare>
RandomAccessIterator
partial_sort_copy(InputIterator _first, InputIterator _last,
                  RandomAccessIterator _dest_f, RandomAccessIterator _dest_l,
                  Compare _comp)
{
    if(_dest_f == _dest_l)
        return _dest_l;

    RandomAccessIterator current = _dest_f;
    for(; _first != _last && current != _dest_l; ++_first, ++current)
        *current = *_first;

    wt::make_heap(_dest_f, current, _comp);
    for(; _first != _last; ++_first)
    {
        if(_comp(*_first, *_dest_f))
            wt::_adjust_heap(_dest_f, decltype(_dest_l - _dest_f)(0),
                             wt::distance(_dest_f, current), *_first, _comp);
    }
    wt::sort_heap(_dest_f, current, _comp);
    return current;
}

//  stable_sort
//  TODO

//  nth_element
//  TODO

//////////////////////////////////////////////////
//  Binary Search Operations (On Sorted Ranges) //
//////////////////////////////////////////////////

//  lower_bound
//  upper_bound
//  equal_range
template <typename ForwardIterator, typename T>
ForwardIterator
lower_bound(ForwardIterator _first, ForwardIterator _last, const T& _value)
{
    if(_first == _last)
        return _last;

    ForwardIterator mid;
    auto len = wt::distance(_first, _last);
    while(len > 0)
    {
        mid = _first;
        auto step = len / 2;
        wt::advance(mid, step);
        if(*mid < _value)
        {
            _first = ++mid;
            len -= (step + 1);
        }
        else
        {
            len = step;
        }
    }
    return _first;
}

template <typename ForwardIterator, typename T, typename Compare>
ForwardIterator
lower_bound(ForwardIterator _first, ForwardIterator _last, const T& _value,
            Compare _comp)
{
    if(_first == _last)
        return _last;

    ForwardIterator mid;
    auto len = wt::distance(_first, _last);
    while(len > 0)
    {
        mid = _first;
        auto step = len / 2;
        wt::advance(mid, step);
        if(_comp(*mid, _value))
        {
            _first = ++mid;
            len -= (step + 1);
        }
        else
        {
            len = step;
        }
    }
    return _first;
}

template <typename ForwardIterator, typename T>
ForwardIterator
upper_bound(ForwardIterator _first, ForwardIterator _last, const T& _value)
{
    if(_first == _last)
        return _last;

    ForwardIterator mid;
    auto len = wt::distance(_first, _last);
    while(len > 0)
    {
        mid = _first;
        auto step = len / 2;
        wt::advance(mid, step);
        if(!(_value < *mid))
        {
            _first = ++mid;
            len -= step + 1;
        }
        else
        {
            len = step;
        }
    }
    return _first;
}

template <typename ForwardIterator, typename T, typename Compare>
ForwardIterator
upper_bound(ForwardIterator _first, ForwardIterator _last, const T& _value,
            Compare _comp)
{
    if(_first == _last)
        return _last;

    ForwardIterator mid;
    auto len = wt::distance(_first, _last);
    while(len > 0)
    {
        mid = _first;
        auto step = len / 2;
        wt::advance(mid, step);
        if(!_comp(_value, *mid))
        {
            _first = ++mid;
            len -= step + 1;
        }
        else
        {
            len = step;
        }
    }
    return _first;
}

template <typename ForwardIterator, typename T>
inline wt::pair<ForwardIterator, ForwardIterator>
equal_range(ForwardIterator _first, ForwardIterator _last, const T& _value)
{
    ForwardIterator e_first = wt::lower_bound(_first, _last, _value);
    ForwardIterator e_last  = wt::upper_bound(e_first, _last, _value);
    return wt::make_pair(e_first, e_last);
}

template <typename ForwardIterator, typename T, typename Compare>
inline wt::pair<ForwardIterator, ForwardIterator>
equal_range(ForwardIterator _first, ForwardIterator _last, const T& _value,
            Compare _comp)
{
    ForwardIterator e_first = wt::lower_bound(_first, _last, _value, _comp);
    ForwardIterator e_last  = wt::upper_bound(_first, _last, _value, _comp);
    return wt::make_pair(e_first, e_last);
}

//  binary_search
template <typename ForwardIterator, typename T>
inline bool
binary_search(ForwardIterator _first, ForwardIterator _last, const T& _value)
{
    _first = wt::lower_bound(_first, _last, _value);
    return !(_first == _last) && !(_value < *_first);
}

template <typename ForwardIterator, typename T, typename Compare>
inline bool
binary_search(ForwardIterator _first, ForwardIterator _last, const T& _value,
              Compare _comp)
{
    _first = wt::lower_bound(_first, _last, _value, _comp);
    return !(_first == _last) && !_comp(_value, *_first);
}

//////////////////////////////////////
// Set Operations(On Sorted Ranges) //
//////////////////////////////////////

//  merge
template <typename InputIterator1, typename InputIterator2,
          typename OutputIterator>
OutputIterator
merge(InputIterator1 _first1, InputIterator1 _last1,
      InputIterator2 _first2, InputIterator2 _last2,
      OutputIterator _dest)
{
    while(_first1 != _last1 && _first2 != _last2)
    {
        if(*_first2 < *_first1)
            *_dest++ = *_first2++;
        else
            *_dest++ = *_first1++;
    }
    return _first1 == _last1 ? wt::copy(_first2, _last2, _dest)
            : wt::copy(_first1, _last1, _dest);
}

template <typename InputIterator1, typename InputIterator2,
          typename OutputIterator, typename Compare>
OutputIterator
merge(InputIterator1 _first1, InputIterator1 _last1,
      InputIterator2 _first2, InputIterator2 _last2,
      OutputIterator _dest, Compare _comp)
{
    while(_first1 != _last1 && _first2 != _last2)
    {
        if(_comp(*_first2, *_first1))
            *_dest++ = *_first2++;
        else
            *_dest++ = *_first1++;
    }
    return _first1 == _last1 ? wt::copy(_first2, _last2, _dest)
            : wt::copy(_first1, _last1, _dest);
}

//  inplace_sort
//  TODO

//  includes
template <typename InputIterator1, typename InputIterator2>
bool
includes(InputIterator1 _first1, InputIterator1 _last1,
         InputIterator2 _first2, InputIterator2 _last2)
{
    while(_first2 != _last2)
    {
        if(_first1 == _last1 || *_first2 < *_first1)
            return false;
        if(!(*_first1 < *_first2))
            ++_first2;
        ++_first1;
    }
    return true;
}

template <typename InputIterator1, typename InputIterator2,typename Compare>
bool
includes(InputIterator1 _first1, InputIterator1 _last1,
         InputIterator2 _first2, InputIterator2 _last2,
         Compare _comp)
{
    while(_first2 != _last2)
    {
        if(_first1 == _last1 || _comp(*_first2, *_first1))
            return false;
        if(!_comp(*_first1, *_first2))
            ++_first2;
        ++_first1;
    }
    return true;
}

//  set_difference
template <typename InputIterator1, typename InputIterator2,
          typename OutputIterator>
OutputIterator
set_difference(InputIterator1 _first1, InputIterator1 _last1,
               InputIterator2 _first2, InputIterator2 _last2,
               OutputIterator _dest)
{
    while(_first1 != _last1 && _first2 != _last2)
    {
        if(*_first1 < *_first2)
        {
            *_dest++ = *_first1;
            ++_first1;
        }
        else if(*_first2 < *_first2)
        {
            ++_first2;
        }
        else
        {
            ++_first1;
            ++_first2;
        }
    }
    return _first1 == _last1 ? _dest : wt::copy(_first1, _last1, _dest);
}

template <typename InputIterator1, typename InputIterator2,
          typename OutputIterator, typename Compare>
OutputIterator
set_difference(InputIterator1 _first1, InputIterator1 _last1,
               InputIterator2 _first2, InputIterator2 _last2,
               OutputIterator _dest, Compare _comp)

{
    while(_first1 != _last1 && _first2 != _last2)
    {
        if(_comp(*_first1, *_first2))
        {
            *_dest++ = *_first1;
            ++_first1;
        }
        else if(_comp(*_first2, *_first1))
        {
            ++_first2;
        }
        else
        {
            ++_first1;
            ++_first2;
        }
    }
    return _first1 == _last1 ? _dest : wt::copy(_first1, _last1, _dest);
}

//  set_intersection
template <typename InputIterator1, typename InputIterator2,
          typename OutputIterator>
OutputIterator
set_intersection(InputIterator1 _first1, InputIterator1 _last1,
                 InputIterator2 _first2, InputIterator2 _last2,
                 OutputIterator _dest)
{
    while(_first1 != _last1 && _first2 != _last2)
    {
        if(*_first1 < *_first2)
            ++_first1;
        else if(*_first2 < *_first1)
            ++_first2;
        else
        {
            *_dest++ = *_first1;
            ++_first1;
            ++_first2;
        }
    }
    return _dest;
}

template <typename InputIterator1, typename InputIterator2, 
          typename OutputIterator, typename Compare>
OutputIterator
set_intersection(InputIterator1 _first1, InputIterator1 _last1,
                 InputIterator2 _first2, InputIterator2 _last2,
                 OutputIterator _dest, Compare _comp)
{
    while(_first1 != _last1 && _first2 != _last2)
    {
        if(_comp(*_first1, *_first2))
            ++_first1;
        else if(_comp(*_first2, *_first1))
            ++_first2;
        else
        {
            *_dest++ = *_first1;
            ++_first1;
            ++_first2;
        }
    }
    return _dest;
}

//  set_symmetric_difference
template <typename InputIterator1, typename InputIterator2,
          typename OutputIterator>
OutputIterator
set_symmetric_difference(InputIterator1 _first1, InputIterator1 _last1,
                         InputIterator2 _first2, InputIterator2 _last2,
                         OutputIterator _dest)
{
    while(_first1 != _last1 && _first2 != _last2)
    {
        if(*_first1 < *_first2)
            *_dest++ = *_first1++;
        else if(*_first2 < *_first1)
            *_dest++ = *_first2++;
        else
        {
            ++_first1;
            ++_first2;
        }
    }
    return _first1 == _last1 ? wt::copy(_first2, _last2, _dest)
            : wt::copy(_first1, _last1, _dest);
}

template <typename InputIterator1, typename InputIterator2,
          typename OutputIterator, typename Compare>
OutputIterator
set_symmetric_difference(InputIterator1 _first1, InputIterator1 _last1,
                         InputIterator2 _first2, InputIterator2 _last2,
                         OutputIterator _dest, Compare _comp)
{
    while(_first1 != _last1 && _first2 != _last2)
    {
        if(_comp(*_first1, *_first2))
            *_dest++ = *_first1++;
        else if(_comp(*_first2, *_first1))
            *_dest++ = *_first2++;
        else
        {
            ++_first1;
            ++_first2;
        }
    }
    return _first1 == _last1 ? wt::copy(_first2, _last2, _dest)
            : wt::copy(_first1, _last1, _dest);
}

//  set_union
template <typename InputIterator1, typename InputIterator2,
          typename OutputIterator>
OutputIterator
set_union(InputIterator1 _first1, InputIterator1 _last1,
          InputIterator2 _first2, InputIterator2 _last2,
          OutputIterator _dest)
{
    while(_first1 != _last1 && _first2 != _last2)
    {
        if(*_first2 < *_first1)
            *_dest++ = *_first2++;
        else
        {
            if(!(*_first1 < *_first2))
                ++_first2;
            *_dest++ = *_first1++;
        }
    }
    return _first1 == _last1 ? wt::copy(_first2, _last2, _dest)
            : wt::copy(_first1, _last1, _dest);
}

template <typename InputIterator1, typename InputIterator2,
          typename OutputIterator, typename Compare>
OutputIterator
set_union(InputIterator1 _first1, InputIterator1 _last1,
          InputIterator2 _first2, InputIterator2 _last2,
          OutputIterator _dest, Compare _comp)
{
    while(_first1 != _last1 && _first2 != _last2)
    {
        if(_comp(*_first2, *_first1))
            *_dest++ = *_first2++;
        else
        {
            if(!_comp(*_first1, *_first2))
                ++_first2;
            *_dest++ = *_first1++;
        }
    }
    return _first1 == _last1 ? wt::copy(_first2, _last2, _dest)
            : wt::copy(_first1, _last1, _dest);
}

////////////////////////////////
// Minimum/Maximum Operations //
////////////////////////////////

//  max_element
//  min_element
template <typename ForwardIterator>
constexpr ForwardIterator
max_element(ForwardIterator _first, ForwardIterator _last)
{
    if(_first == _last)
        return _last;
    ForwardIterator largest = _first;
    while(++_first != _last)
    {
        if(*largest < *_first)
            largest = _first;
    }
    return largest;
}

template <typename ForwardIterator, typename Compare>
constexpr ForwardIterator
max_element(ForwardIterator _first, ForwardIterator _last, Compare _comp)
{
    if(_first == _last)
        return _last;
    ForwardIterator largest = _first;
    while(++_first != _last)
    {
        if(_comp(*largest, *_first))
            largest = _first;
    }
    return largest;
}

template <typename ForwardIterator>
constexpr ForwardIterator
min_element(ForwardIterator _first, ForwardIterator _last)
{
    if(_first == _last)
        return _last;
    ForwardIterator smallest = _first;
    while(++_first != _last)
    {
        if(*_first < *smallest)
            smallest = _first;
    }
    return smallest;
}

template <typename ForwardIterator, typename Compare>
constexpr ForwardIterator
min_element(ForwardIterator _first, ForwardIterator _last, Compare _comp)
{
    if(_first == _last)
        return _last;
    ForwardIterator smallest = _first;
    while(++_first != _last)
    {
        if(_comp(*_first, *smallest))
            smallest = _first;
    }
    return smallest;
}

//  max
//  min
template <typename T>
constexpr T
max(std::initializer_list<T> _il)
{
    return *wt::max_element(_il.begin(), _il.end());
}

template <typename T, typename Compare>
constexpr T
max(std::initializer_list<T> _il, Compare _comp)
{
    return wt::max_element(_il.begin(), _il.end(), _comp);
}

template <typename T>
constexpr T
min(std::initializer_list<T> _il)
{
    return *wt::min_element(_il.begin(), _il.end());
}

template <typename T, typename Compare>
constexpr T
min(std::initializer_list<T> _il, Compare _comp)
{
    return *wt::min_element(_il.begin(), _il.end(), _comp);
}

//  minmax_element
template <typename ForwardIterator>
constexpr wt::pair<ForwardIterator, ForwardIterator>
minmax_element(ForwardIterator _first, ForwardIterator _last)
{
    if(_first == _last)
        return wt::make_pair(_first, _first);
    ForwardIterator largest = _first;
    ForwardIterator smallest = _first;
    while(++_first != _last)
    {
        if(*_first < *smallest)
            smallest = _first;
        else if(!(*_first < *largest))
            largest = _first;
    }
    return wt::make_pair(smallest, largest);
}

template <typename ForwardIterator, typename Compare>
constexpr wt::pair<ForwardIterator, ForwardIterator>
minmax_element(ForwardIterator _first, ForwardIterator _last, Compare _comp)
{
    if(_first == _last)
        return wt::make_pair(_first, _first);
    ForwardIterator largest = _first;
    ForwardIterator smallest = _first;
    while(++_first != _last)
    {
        if(_comp(*_first, *smallest))
            smallest = _first;
        else if(!_comp(*_first, *largest))
            largest = _first;
    }
    return wt::make_pair(smallest, largest);
}

//  minmax
template <typename T>
constexpr wt::pair<const T&, const T&>
minmax(const T& _a, const T& _b)
{
    return _b < _a ? wt::make_pair(_b, _a) : wt::make_pair(_a, _b);
}

template <typename T, typename Compare>
constexpr wt::pair<const T&, const T&>
minmax(const T& _a, const T& _b, Compare _comp)
{
    return _comp(_b, _a) ? wt::make_pair(_b, _a) : wt::make_pair(_a, _b);
}

template <typename T>
constexpr wt::pair<T, T>
minmax(std::initializer_list<T> _il)
{
    auto result = wt::minmax_element(_il.begin(), _il.end());
    return wt::make_pair(*result.first, *result.second);
}

template <typename T, typename Compare>
constexpr wt::pair<T, T>
minmax(std::initializer_list<T> _il, Compare _comp)
{
    auto result = wt::minmax_element(_il.begin(), _il.end(), _comp);
    return wt::make_pair(*result.first, *result.second);
}

//  clamp
template <typename T>
constexpr const T&
clamp(const T& _value, const T& _low, const T& _high)
{
    return _value < _low ? _low
            : (_high < _value ? _high : _value);
}

template <typename T, typename Compare>
constexpr const T& 
clamp(const T& _value, const T& _low, const T& _high, Compare _comp)
{
    return _comp(_value, _low) ? _low 
            : (_comp(_high, _value) ? _high : _value);
}

//  is_permutation
template <typename ForwardIterator1, typename ForwardIterator2>
bool
is_permutation(ForwardIterator1 _first1, ForwardIterator1 _last1,
               ForwardIterator2 _first2)
{
    auto result = wt::mismatch(_first1, _last1, _first2);
    _first1 = result.first;
    _first2 = result.second;
    if(_first1 != _last1)
    {
        ForwardIterator2 _last2 = _first2;
        wt::advance(_last2, wt::distance(_first1, _last1));
        for(ForwardIterator1 current = _first1; current != _last1; ++current)
        {
            if(current == wt::find(_first1, current, *current))
            {
                auto n = wt::count(_first2, _last2, *current);
                if(n == 0 || n != wt::count(current, _last1, *current))
                    return false;
            }
        }
    }
    return true;
}

template <typename ForwardIterator1, typename ForwardIterator2,
          typename BinaryPredicate>
bool
is_permutation(ForwardIterator1 _first1, ForwardIterator1 _last1,
               ForwardIterator2 _first2, BinaryPredicate _pred)
{
    auto result = wt::mismatch(_first1, _last1, _first2, _pred);
    _first1 = result.first;
    _first2 = result.second;
    if(_first1 != _last1)
    {
        ForwardIterator2 _last2 = _first2;
        wt::advance(_last2, wt::distance(_first1, _last1));
        for(ForwardIterator1 current = _first1; current != _last1; ++current)
        {
            auto p = [_pred, current](const auto& val) 
                     { return _pred(val, *current); };
            if(current == wt::find_if(_first1, current, p))
            {
                auto n = wt::count_if(_first2, _last2, p);
                if(n == 0 || n != wt::count_if(current, _last1, p))
                    return false;
            }
        }
    }
    return true;
}

template <typename ForwardIterator1, typename ForwardIterator2>
bool 
is_permutation(ForwardIterator1 _first1, ForwardIterator1 _last1,
               ForwardIterator2 _first2, ForwardIterator2 _last2)
{
    if(wt::distance(_first1, _last1) != wt::distance(_first2, _last2))
        return false;
    return wt::is_permutation(_first1, _last1, _first2);
}

template <typename ForwardIterator1, typename ForwardIterator2,
          typename BinaryPredicate>
bool
is_permutation(ForwardIterator1 _first1, ForwardIterator1 _last1,
               ForwardIterator2 _first2, ForwardIterator2 _last2,
               BinaryPredicate _pred)
{
    if(wt::distance(_first1, _last1) != wt::distance(_first2, _last2))
        return false;
    return wt::is_permutation(_first1, _last1, _first2, _pred);
}

//  next_permutation
template <typename BidirectionalIterator>
bool
next_permutation(BidirectionalIterator _first, BidirectionalIterator _last)
{
    if(_first == _last)
        return false;
    BidirectionalIterator sp1 = _last;
    if(_first == --sp1)
        return false;

    while(true)
    {
        BidirectionalIterator rs = sp1;
        if(*--sp1 < *rs)
        {
            BidirectionalIterator sp2 = _last;
            while(!(*sp1 < *--sp2))
                ;
            wt::iter_swap(sp1, sp2);
            wt::reverse(rs, _last);
            return true;
        }
        if(sp1 == _first)
        {
            wt::reverse(_first, _last);
            return false;
        }
    }
}

template <typename BidirectionalIterator, typename Compare>
bool
next_permutation(BidirectionalIterator _first, BidirectionalIterator _last,
                 Compare _comp)
{
    if(_first == _last)
        return false;
    BidirectionalIterator sp1 = _last;
    if(_first == --sp1)
        return false;

    while(true)
    {
        BidirectionalIterator rs = sp1;
        if(_comp(*--sp1, *rs))
        {
            BidirectionalIterator sp2 = _last;
            while(!_comp(*sp1, *--sp2))
                ;
            wt::iter_swap(sp1, sp2);
            wt::reverse(rs, _last);
            return true;
        }
        if(sp1 == _first)
        {
            wt::reverse(_first, _last);
            return false;
        }
    }
}

//  prev_permutation
template <typename BidirectionalIterator>
bool
prev_permutation(BidirectionalIterator _first, BidirectionalIterator _last)
{
    if(_first == _last)
        return false;
    BidirectionalIterator sp1 = _last;
    if(_first == --sp1)
        return false;

    while(true)
    {
        BidirectionalIterator rs = sp1;
        if(*rs < *--sp1)
        {
            BidirectionalIterator sp2 = _last;
            while(!(*--sp2 < *sp1))
                ;
            wt::iter_swap(sp1, sp2);
            wt::reverse(rs, _last);
            return true;
        }
        if(sp1 == _first)
        {
            wt::reverse(_first, _last);
            return false;
        }
    }
}

template <typename BidirectionalIterator, typename Compare>
bool
prev_permutation(BidirectionalIterator _first, BidirectionalIterator _last,
                 Compare _comp)
{
    if(_first == _last)
        return false;
    BidirectionalIterator sp1 = _last;
    if(_first == --sp1)
        return false;

    while(true)
    {
        BidirectionalIterator rs = sp1;
        if(_comp(*rs, *--sp1))
        {
            BidirectionalIterator sp2 = _last;
            while(!_comp(*--sp2, *sp1))
                ;
            wt::iter_swap(sp1, sp2);
            wt::reverse(rs, _last);
            return true;
        }
        if(sp1 == _first)
        {
            wt::reverse(_first, _last);
            return false;
        }
    }
}






} // namespace wt
#endif