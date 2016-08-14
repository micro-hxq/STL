#ifndef _STL_WT_UNINITIALIZED_HPP_
#define _STL_WT_UNINITIALIZED_HPP_

/**
 *  depend on:
 *            "type_traits.hpp"
 *            "../algorithm/wt_algo_base.hpp"
 *            "../iterator/wt_iterator_base.hpp"
 *            "../utility/wt_pair.hpp"
 *            
 */

namespace wt{

////////////////////////
// uninitialized_copy //
////////////////////////
template <typename InputIterator, typename ForwardIterator>
inline ForwardIterator 
_uninitialized_copy_aux(InputIterator _first, InputIterator _last,
                        ForwardIterator _result, true_type)
{
    return wt::copy(_first, _last, _result);
}

template <typename InputIterator, typename ForwardIterator>
ForwardIterator
_uninitialized_copy_aux(InputIterator _first, InputIterator _last,
                        ForwardIterator _result, false_type)
{
    ForwardIterator _current = _result;
    try {
        for(; _first != _last; ++_first, ++_current)
        {
            wt::construct(&*_current, *_first);
        }
    }
    catch(...) {
        wt::destroy(_result, _current);
        throw;
    }
    return _current;
}

template <typename InputIterator, typename ForwardIterator, typename T>
inline ForwardIterator
_uninitialized_copy(InputIterator _first, InputIterator _last,
                    ForwardIterator _result, T*)
{
    return wt::_uninitialized_copy_aux(_first, _last, _result, is_pod<T>());
}

template <typename InputIterator, typename ForwardIterator>
inline ForwardIterator
uninitialized_copy(InputIterator _first, InputIterator _last, ForwardIterator _result)
{
    return wt::_uninitialized_copy(_first, _last, _result, _VALUE_TYPE(_result));
}

inline char* uninitialized_copy(const char* _first, const char* _last,
                                char* _result)
{
    memmove(_result, _first, _last - _first);
    return _result + (_last - _first);
}

inline wchar_t* uninitialized_copy(const wchar_t* _first, const wchar_t* _last,
                                   wchar_t* _result)
{
    memmove(_result, _first, sizeof(wchar_t) * (_last - _first));
    return _result + (_last - _first);
}

//////////////////////////
// uninitialized_copy_n //
//////////////////////////
template <typename InputIterator, typename Size, typename ForwardIterator>
wt::pair<InputIterator, ForwardIterator>
_uninitialized_copy_n(InputIterator _first, Size _count,
                      ForwardIterator _result, input_iterator_tag)
{
    ForwardIterator _current = _result;
    try{
        for(; _count > 0; ++_first, ++_current, --_count)
        {
            wt::construct(&*_current, *_first);
        }
    }
    catch(...){
        wt::destroy(_result, _current);
        throw;
    }
    return wt::pair<InputIterator, ForwardIterator>(_first,_current);
}

template <typename RandomAccessIterator, typename Size, typename ForwardIterator>
inline wt::pair<RandomAccessIterator, ForwardIterator>
_uninitialized_copy_n(RandomAccessIterator _first, Size _count,
                      ForwardIterator _result, random_access_iterator_tag)
{
    RandomAccessIterator _last = _first + _count;
    return wt::pair<RandomAccessIterator, ForwardIterator>(_last,
                    wt::uninitialized_copy(_first, _last, _result));
}

template <typename InputIterator, typename Size, typename ForwardIterator>
inline wt::pair<InputIterator, ForwardIterator>
uninitialized_copy_n(InputIterator _first, Size _count, ForwardIterator _result)
{
    return wt::_uninitialized_copy_n(_first, _count, _result,
                                     _ITERATOR_CATEGORY(_first));
}

////////////////////////
// uninitialized_fill //
////////////////////////
template <typename ForwardIterator, typename T>
inline void _uninitialized_fill_aux(ForwardIterator _first, ForwardIterator _last, 
                                const T& _value, true_type)
{
    wt::fill(_first, _last, _value);
}

template <typename ForwardIterator, typename T>
void _uninitialized_fill_aux(ForwardIterator _first, ForwardIterator _last,
                                    const T& _value, false_type)
{
    ForwardIterator _current = _first;
    try{
        for(; _current != _last; ++_current)
        {
            wt::construct(&*_current, _value);
        }
    }
    catch(...){
        wt::destroy(_first, _current);
        throw;
    }
}

template <typename ForwardIterator, typename T, typename U>
inline void _uninitialized_fill(ForwardIterator _first, ForwardIterator _last,
                                const T& _value, U*)
{
    wt::_uninitialized_fill_aux(_first, _last, _value, wt::is_pod<U>());
}

template <typename ForwardIterator, typename T>
inline void uninitialized_fill(ForwardIterator _first, ForwardIterator _last,
                               const T& _value)
{
    wt::_uninitialized_fill(_first, _last, _value, _VALUE_TYPE(_first));
}

//////////////////////////
// uninitialized_fill_n //
//////////////////////////
template <typename ForwardIterator, typename Size, typename T>
inline ForwardIterator
_uninitialized_fill_n_aux(ForwardIterator _first, Size _count,
                          const T& _value, true_type)
{
    return wt::fill_n(_first, _count, _value);
}

template <typename ForwardIterator, typename Size, typename T>
ForwardIterator
_uninitialized_fill_n_aux(ForwardIterator _first, Size _count,
                          const T& _value, false_type)
{
    ForwardIterator _current = _first;
    try{
        for(; _count > 0; ++_current, --_count)
        {
            wt::construct(&*_current, _value);
        }
    }
    catch(...){
        wt::destroy(_first, _current);
        throw;
    }
    return _current;
}

template <typename ForwardIterator, typename Size, typename T, typename U>
inline ForwardIterator
_uninitialized_fill_n(ForwardIterator _first, Size _count,
                      const T& _value, U*)
{
    return wt::_uninitialized_fill_n_aux(_first, _count, _value, 
                                         wt::is_pod<U>());
}

template <typename ForwardIterator, typename Size, typename T>
inline ForwardIterator
uninitialized_fill_n(ForwardIterator _first, Size _count, const T& _value)
{
    return wt::_uninitialized_fill_n(_first, _count, _value, 
                                     _VALUE_TYPE(_first));
}

} // namespace wt

#endif