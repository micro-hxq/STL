#ifndef _STL_WT_ALGORITHM_HPP_
#define _STL_WT_ALGORITHM_HPP_

namespace wt{

///////////////////////////////////////
// non-modifying sequence oeprations //
///////////////////////////////////////
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

template <typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator1 search(ForwardIterator1 _first, ForwardIterator1 _last,
                        ForwardIterator2 _s_first, ForwardIterator2 _s_last)
{
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

template <typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator1 find_end(ForwardIterator1 _first, ForwardIterator1 _last,
                          ForwardIterator2 _s_first, ForwardIterator2 _s_last)
{
    return _find_end_dispatch(_first, _last, _s_first, _s_last,
                              _ITERATOR_CATEGORY(_first),
                              _ITERATOR_CATEGORY(_s_first));
}
template <typename ForwardIterator1, typename ForwardIterator2,
          typename BinaryPredicate>
ForwardIterator1 find_end(ForwardIterator1 _first, ForwardIterator1 _last,
                          ForwardIterator2 _s_first, ForwardIterator2 _s_last,
                          BinaryPredicate _pred)
{
    return _find_end_dispatch(_first, _last, _s_first, _s_last, _pred,
                              _ITERATOR_CATEGORY(_first),
                              _ITERATOR_CATEGORY(_s_first));
}

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
ForwardIterator2 
swap_ranges(ForwardIterator1 _first1, ForwardIterator1 _last1,
            ForwardIterator2 _first2)
{
  for(; _first1 != _last1; ++_first1, ++_first2)
    wt::iter_swap(_first1, _first2);
  return _first2;
}







} // namespace wt
#endif