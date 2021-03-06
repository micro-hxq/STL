#ifndef _STL_WT_ALGO_BASE_HPP_
#define _STL_WT_ALGO_BASE_HPP_ 

namespace wt{

template <typename T>
void swap(T& _a, T& _b)
{
    T temp = _a;
    _a = _b;
    _b = temp;
}

template <typename ForwardIterator1, typename ForwardIterator2>
inline void iter_swap(ForwardIterator1 _a, ForwardIterator2 _b)
{
    wt::swap(*_a, *_b);
}

/////////////////
// min and max //
/////////////////
template <typename T>
constexpr const T& min(const T& _a, const T& _b)
{
    return _a < _b ? _a : _b;
}

template <typename T>
constexpr const T& max(const T& _a, const T& _b)
{
    return _a < _b ? _b : _a;
}

template <typename T, typename Compare>
constexpr const T& min(const T& _a, const T& _b, Compare _comparetor)
{
    return _comparetor(_a, _b) ? _a : _b;
}

template <typename T, typename Compare>
constexpr const T& max(const T& _a, const T& _b, Compare _comparetor)
{
    return _comparetor(_a, _b) ? _b : _a;
}

/////////////////////
// underlying copy //
/////////////////////
template <typename InputIterator, typename OutputIterator, typename Distance>
inline OutputIterator _copy(InputIterator _first, InputIterator _last,
                            OutputIterator _dest, wt::input_iterator_tag,
                            Distance* )
{
    for(; _first != _last; ++_first, ++_dest)
    {
        *_dest = *_first;
    }
    return _dest;
}

template <typename RandomAccessIterator, typename OutputIterator,
          typename Distance>
inline OutputIterator _copy(RandomAccessIterator _first, 
                            RandomAccessIterator _last,
                            OutputIterator _dest,
                            wt::random_access_iterator_tag,
                            Distance* )
{
    for(Distance left = _last - _first; left > 0; --left)
    {
        *_dest = *_first;
        ++_dest;
        ++_first;
    }
    return _dest;
}

template <typename T>
inline T* _copy_trivial(const T* _first, const T* _last, T* _dest)
{
    memmove(_dest, _first, sizeof(T) * (_last - _first));
    return _dest + (_last - _first);
}

template <typename InputIterator, typename OutputIterator>
inline OutputIterator _copy_aux2(InputIterator _first, InputIterator _last,
                                 OutputIterator _dest, wt::true_type )
{
    return wt::_copy(_first, _last, _dest,
                     _ITERATOR_CATEGORY(_first),
                     _DIFFERENCE_TYPE(_first));
}                                 

template <typename InputIterator, typename OutputIterator>
inline OutputIterator _copy_aux2(InputIterator _first, InputIterator _last,
                                 OutputIterator _dest, wt::false_type )
{
    return wt::_copy(_first, _last, _dest,
                     _ITERATOR_CATEGORY(_first),
                     _DIFFERENCE_TYPE(_first));
}

template <typename T>
inline T* _copy_aux2(const T* _first, const T* _last, T* _dest, wt::true_type)
{
      memmove(_dest, _first, sizeof(T) * (_last - _first));
      return _dest + (_last - _first);
}

// distinguish between iterator and pointer
template <typename InputIterator, typename OutputIterator, typename T>
inline OutputIterator _copy_aux(InputIterator _first, InputIterator _last,
                                OutputIterator _dest, T* )
{
    return wt::_copy_aux2(_first, _last, _dest, 
                          wt::is_trivially_copy_assignable<T>());
}

template <typename InputIterator, typename OutputIterator>
inline OutputIterator copy(InputIterator _first, InputIterator _last,
                           OutputIterator _dest)
{
    return wt::_copy_aux(_first, _last, _dest, _VALUE_TYPE(_first));
}

///////////////////
// copy backward //
///////////////////
template <typename BidirectionalIterator1, typename BidirectionalIterator2,
          typename Distance>
inline BidirectionalIterator2 _copy_backward(BidirectionalIterator1 _first,
                                             BidirectionalIterator1 _last,
                                             BidirectionalIterator2 _dest,
                                             wt::bidirectional_iterator_tag,
                                             Distance*)
{
    while(_first != _last)
    {
        *--_dest = *--_last;
    }
    return _dest;
}

template <typename RandomAccessIterator, typename BidirectionalIterator,
          typename Distance>
inline BidirectionalIterator _copy_backward(RandomAccessIterator _first,
                                            RandomAccessIterator _last,
                                            BidirectionalIterator _dest,
                                            wt::random_access_iterator_tag,
                                            Distance* )
{
    for(Distance left = _last - _first; left > 0; --left)
    {
        *--_dest = *--_last;
    }
    return _dest;
}

template <typename BidirectionalIterator1, typename BidirectionalIterator2>
inline BidirectionalIterator2 copy_backward(BidirectionalIterator1 _first,
                                            BidirectionalIterator1 _last,
                                            BidirectionalIterator2 _dest)
{
    return wt::_copy_backward(_first, _last, _dest,
                              _ITERATOR_CATEGORY(_first),
                              _DIFFERENCE_TYPE(_first));
}

////////////
// copy_n //
////////////
template <typename InputIterator, typename Size, typename OutputIterator>
wt::pair<InputIterator, OutputIterator>
_copy_n(InputIterator _first, Size _count, OutputIterator _result, 
        wt::input_iterator_tag)
{
    for(; _count > 0; --_count)
    {
        *_result = *_first;
        ++_result;
        ++_first;
    }
    return wt::pair<InputIterator, OutputIterator>(_first, _result);
}

template <typename RandomAccessIterator, typename Size, typename OutputIterator>
inline wt::pair<RandomAccessIterator, OutputIterator>
_copy_n(RandomAccessIterator _first, Size _count, OutputIterator _result,
        wt::random_access_iterator_tag)
{
    if(_count <= 0)
        return wt::pair<RandomAccessIterator, OutputIterator>(_first, _result);

    RandomAccessIterator _last = _first + _count;
    return wt::pair<RandomAccessIterator, OutputIterator>(_last,
                                            wt::copy(_first, _last, _result));
}

template <typename InputIterator,typename Size, typename OutputIterator>
inline wt::pair<InputIterator, OutputIterator>
_copy_n(InputIterator _first, Size _count, OutputIterator _result)
{
    return wt::_copy_n(_first, _count, _result, _ITERATOR_CATEGORY(_first));
}

template <typename InputIterator, typename Size, typename OutputIterator>
inline wt::pair<InputIterator, OutputIterator>
copy_n(InputIterator _first, Size _count, OutputIterator _result)
{
    return wt::_copy_n(_first, _count, _result);
}

/////////////////////
// fill and fill_n //
/////////////////////
template <typename ForwardIterator, typename T>
void fill(ForwardIterator _first, ForwardIterator _last, const T& _value)
{
    for(; _first != _last; ++_first)
    {
        *_first = _value;
    }
}

template <typename OutputIterator, typename Size, typename T>
OutputIterator fill_n(OutputIterator _first, Size _count, const T& _value)
{
    for(; _count > 0; --_count)
    {
        *_first = _value;
        ++_first;
    }
    return _first;
}

/**
 *  one byte optimization
 */
inline void fill(unsigned char* _first, unsigned char* _last, 
                 unsigned char _c)
{
    memset(_first, _c, _last - _first);
}

inline void fill(signed char* _first, signed char* _last,
                 signed char _c)
{
    memset(_first, static_cast<unsigned char>(_c), _last - _first);
}

inline void fill(char* _first, char* _last, char _c)
{
    memset(_first, static_cast<unsigned char>(_c), _last - _first);
}

template <typename Size>
inline unsigned char* fill_n(unsigned char* _first, Size _count,
                             unsigned char _c)
{
    wt::fill(_first, _first + _count, _c);
    return _first + _count;
}

template <typename Size>
inline signed char* fill_n(signed char* _first, Size _count,
                           signed char _c)
{
    wt::fill(_first, _first + _count, _c);
    return _first + _count;
}

template <typename Size>
inline char* fill_n(char* _first, Size _count, char _c)
{
    wt::fill(_first, _first + _count, _c);
    return _first + _count;
}

///////////
// equal //
///////////
template <typename InputIterator1, typename InputIterator2>
bool equal(InputIterator1 _first1, InputIterator1 _last1,
           InputIterator2 _first2)
{
    for(; _first1 != _last1; ++_first1, ++_first2)
    {
        if(*_first1 != *_first2)
            return false;
    }
    return true;
}

template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
bool equal(InputIterator1 _first1, InputIterator1 _last1,
           InputIterator2 _first2, BinaryPredicate pred)
{
    for(; _first1 != _last1; ++_first1, ++_first2)
    {
        if(!pred(*_first1, *_first2))
            return false;
    }
    return true;
}           

template <typename InputIterator1, typename InputIterator2>
bool _equal_dispatch(InputIterator1 _first1, InputIterator1 _last1,
                     InputIterator2 _first2, InputIterator2 _last2,
                     wt::input_iterator_tag, wt::input_iterator_tag)
{
    for(; _first1 != _last1 && _first2 != _last2; ++_first1, ++_first2)
    {
        if(*_first1 != *_first2)
            return false;
    }
    return (_first1 == _last1 && _first2 == _last2);
}

template <typename ForwardIterator1, typename ForwardIterator2>
bool _equal_dispatch(ForwardIterator1 _first1, ForwardIterator1 _last1,
                     ForwardIterator2 _first2, ForwardIterator2 _last2,
                     wt::forward_iterator_tag, wt::forward_iterator_tag)
{
    if(wt::distance(_first1, _last1) != wt::distance(_first2, _last2))
        return false;
    for(; _first1 != _last1; ++_first1, ++_first2)
    {
        if(*_first1 != *_first2)
            return false;
    }
    return true;
}

template <typename InputIterator1, typename InputIterator2>
inline bool equal(InputIterator1 _first1, InputIterator1 _last1,
                  InputIterator2 _first2, InputIterator2 _last2)
{
    return wt::_equal_dispatch(_first1, _last1, _first2, _last2,
                               _ITERATOR_CATEGORY(_first1),
                               _ITERATOR_CATEGORY(_first2));
}

template <typename InputIterator1, typename InputIterator2,
          typename BinaryPredicate>
bool _equal_dispatch(InputIterator1 _first1, InputIterator1 _last1,
                     InputIterator2 _first2, InputIterator2 _last2,
                     BinaryPredicate pred, wt::input_iterator_tag,
                     wt::input_iterator_tag)
{
    for(; _first1 != _last1 && _first2 != _last2; ++_first1, ++_first2)
    {
        if(!pred(*_first1, *_first2))
            return false;
    }
    return (_first1 == _last1 && _first2 == _last2);
}

template <typename ForwardIterator1, typename ForwardIterator2,
          typename BinaryPredicate>
bool _equal_dispatch(ForwardIterator1 _first1, ForwardIterator1 _last1,
                     ForwardIterator2 _first2, ForwardIterator2 _last2,
                     BinaryPredicate pred, wt::forward_iterator_tag,
                     wt::forward_iterator_tag)
{
    if(wt::distance(_first1, _last1) != wt::distance(_first2, _last2))
        return false;
    for(; _first1 != _last1; ++_first1, ++_first2)
    {
        if(!pred(*_first1, *_first2))
            return false;
    }
    return true;
}           

template <typename InputIterator1, typename InputIterator2,
          typename BinaryPredicate>
inline bool equal(InputIterator1 _first1, InputIterator1 _last1,
                  InputIterator2 _first2, InputIterator2 _last2,
                  BinaryPredicate pred)
{
    return wt::_equal_dispatch(_first1, _last1, _first2, _last2, pred,
                               _ITERATOR_CATEGORY(_first1),
                               _ITERATOR_CATEGORY(_first2));
}
/////////////////////////////
// lexicographical_compare //
/////////////////////////////
template <typename InputIterator1, typename InputIterator2>
bool lexicographical_compare(InputIterator1 _first1, InputIterator1 _last1,
                             InputIterator2 _first2, InputIterator2 _last2)
{
    for(; _first1 != _last1 && _first2 != _last2; ++_first1, ++_first2)
    {
        if(*_first1 < *_first2)
            return true;
        if(*_first2 < *_first1)
            return false;
    }
    return _first1 == _last1 && _first2 != _last2;
}                             

template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
bool lexicographical_compare(InputIterator1 _first1, InputIterator1 _last1,
                             InputIterator2 _first2, InputIterator2 _last2,
                             BinaryPredicate pred)
{
    for(; _first1 != _last1 && _first2 != _last2; ++_first1, ++_first2)
    {
        if(pred(*_first1, *_first2))
            return true;
        if(pred(*_first2, *_first1))
            return false;
    }
    return _first1 == _last1 && _first2 != _last2;
}

/**
 *  return -1 if the first range greater than the second.
 *  return 1  if the second range greater than the first.
 *  return 0  if two range are equal (both length and element) 
 */
template <typename InputIterator1, typename InputIterator2>
int lexicographical_compare_3way(InputIterator1 _first1, InputIterator1 _last1,
                                 InputIterator2 _first2, InputIterator2 _last2)
{
    for(; _first1 != _last1 && _first2 != _last2; ++_first1, ++_first2)
    {
        if(*_first1 < *_first2)
            return -1;
        if(*_first2 < *_first1)
            return 1;
    }
    if(_first1 != _last1)
        return 1;
    return _first2 != _last2;
}                                 

template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
int lexicographical_compare_3way(InputIterator1 _first1, InputIterator1 _last1,
                                 InputIterator2 _first2, InputIterator2 _last2,
                                 BinaryPredicate pred)
{
    for(; _first1 != _last1 && _first2 != _last2; ++_first1, ++_first2)
    {
        if(pred(*_first1, *_first2))
            return -1;
        if(pred(*_first2, *_first1))
            return 1;
    }
    if(_first1 != _last1)
        return 1;
    return _first2 != _last2;
}

} // namespace wt


#endif