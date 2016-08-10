#ifndef _STL_WT_HEAP_HPP_
#define _STL_WT_HEAP_HPP_

namespace wt {

template <typename RandomAccessIterator, typename Distance, typename T>
void _push_heap(RandomAccessIterator _first, Distance _hole, Distance _top,
                T _value)
{
    Distance parent = (_hole - 1) / 2;
    while(_hole > _top && *(_first + parent) < _value)
    {
        *(_first + _hole) = wt::move(*(_first + parent));
        _hole = parent;
        parent = (_hole - 1) / 2;
    }
    *(_first + _hole) = wt::move(_value);
}

template <typename RandomAccessIterator, typename Distance, typename T>
inline void _push_heap_aux(RandomAccessIterator _first, RandomAccessIterator _last,
                           Distance*, T*)
{
    wt::_push_heap(_first, Distance((_last - _first) - 1), Distance(0),
                   wt::move(*(_last - 1)));
}

template <typename RandomAccessIterator>
inline void push_heap(RandomAccessIterator _first, RandomAccessIterator _last)
{
    wt::_push_heap_aux(_first, _last, _DIFFERENCE_TYPE(_first),
                       _VALUE_TYPE(_first));
}

template <typename RandomAccessIterator, typename Distance, typename T,
          typename Compare>
void _push_heap(RandomAccessIterator _first, Distance _hole, Distance _top,
                T _value, Compare _comp)
{
    Distance parent = (_hole - 1) / 2;
    while(_hole > _top && _comp(*(_first + parent), _value))
    {
        *(_first + _hole) = wt::move(*(_first + parent));
        _hole = parent;
        parent = (_hole - 1) / 2;
    }
    *(_first + _hole) = wt::move(_value);
}

template <typename RandomAccessIterator, typename Distance, typename T,
          typename Compare>
inline void 
_push_heap_aux(RandomAccessIterator _first, RandomAccessIterator _last,
               Distance*, T*, Compare _comp)
{
    wt::_push_heap(_first, Distance((_last - _first) - 1), Distance(0),
                   wt::move(*(_last - 1)), _comp);
}

template <typename RandomAccessIterator, typename Compare>
inline void 
push_heap(RandomAccessIterator _first, RandomAccessIterator _last,
          Compare _comp)
{
    wt::_push_heap_aux(_first, _last, _DIFFERENCE_TYPE(_first),
                       _VALUE_TYPE(_first), _comp);
}

template <typename RandomAccessIterator, typename Distance, typename T>
void _adjust_heap(RandomAccessIterator _first, Distance _hole, Distance _len,
                  T _value)
{
    Distance top = _hole;
    Distance child = 2 * (_hole + 1);
    while(child < _len)
    {
        if(*(_first + child) < *(_first + child - 1))
            --child;
        *(_first + _hole) = wt::move(*(_first + child));
        _hole = child;
        child = 2 * (_hole + 1);
    }
    if(child == _len)
    {
        --child;
        *(_first + _hole) = wt::move(*(_first + child));
        _hole = child;
    }
    wt::_push_heap(_first, _hole, top, wt::move(_value));
}

template <typename RandomAccessIterator, typename Distance, typename T>
inline void 
_pop_heap(RandomAccessIterator _first, RandomAccessIterator _last,
          RandomAccessIterator _result, Distance*, T _value)
{
    *_result = wt::move(*_first);
    wt::_adjust_heap(_first, Distance(0), _last - _first, wt::move(_value));
}

template <typename RandomAccessIterator>
inline void pop_heap(RandomAccessIterator _first, RandomAccessIterator _last)
{
    wt::_pop_heap(_first, _last - 1, _last - 1, _DIFFERENCE_TYPE(_first), 
                  wt::move(*(_last - 1)));
}

template <typename RandomAccessIterator, typename Distance, typename T,
          typename Compare>
void _adjust_heap(RandomAccessIterator _first, Distance _hole, Distance _len,
                  T _value, Compare _comp)
{
    Distance top = _hole;
    Distance child = 2 * (_hole + 1);
    while(child < _len)
    {
        if(_comp(*(_first + child), *(_first + child - 1)))
            --child;
        *(_first + _hole) = wt::move(*(_first + child));
        _hole = child;
        child = 2 * (_hole + 1);
    }
    if(child == _len)
    {
        --child;
        *(_first + _hole) = wt::move(*(_first + child));
        _hole = child;
    }
    wt::_push_heap(_first, _hole, top, wt::move(_value), _comp);
}

template <typename RandomAccessIterator, typename Distance, typename T,
          typename Compare>
inline void 
_pop_heap(RandomAccessIterator _first, RandomAccessIterator _last,
          RandomAccessIterator _result, Distance*, T _value, Compare _comp)
{
    *_result = wt::move(*_first);
    wt::_adjust_heap(_first, Distance(0), _last - _first,
                     wt::move(_value), _comp);
}

template <typename RandomAccessIterator, typename Compare>
inline void pop_heap(RandomAccessIterator _first, RandomAccessIterator _last,
                     Compare _comp)
{
    if(_last - _first > 1)
        wt::_pop_heap(_first, _last - 1, _last - 1, _DIFFERENCE_TYPE(_first),
                      wt::move(*(_last - 1)), _comp);
}

template <typename RandomAccessIterator, typename Distance, typename T>
void _make_heap(RandomAccessIterator _first, RandomAccessIterator _last,
                Distance*, T*)
{
    if(_last - _first > 2)
    {
        const Distance len = _last - _first;
        Distance parent = (len - 2) / 2;
        while(true)
        {
            wt::_adjust_heap(_first, parent, len, wt::move(*(_first + parent)));
            if(parent == 0)
                break;
            --parent;
        }
    }
}

template <typename RandomAccessIterator>
inline void make_heap(RandomAccessIterator _first, RandomAccessIterator _last)
{
    wt::_make_heap(_first, _last, _DIFFERENCE_TYPE(_first),
                   _VALUE_TYPE(_first));
}

template <typename RandomAccessIterator, typename Distance, typename T, 
          typename Compare>
void _make_heap(RandomAccessIterator _first, RandomAccessIterator _last,
                Distance*, T*, Compare _comp)
{
    if(_last - _first > 2)
    {
        const Distance len = _last - _first;
        Distance parent = (len - 2) / 2;
        while(true)
        {
            wt::_adjust_heap(_first, parent, len, wt::move(*(_first + parent)),
                             _comp);
            if(parent == 0)
                break;
            --parent;
        }
    }
}

template <typename RandomAccessIterator, typename Compare>
inline void make_heap(RandomAccessIterator _first, RandomAccessIterator _last,
                      Compare _comp)
{
    wt::_make_heap(_first, _last, _DIFFERENCE_TYPE(_first), _VALUE_TYPE(_first),
                   _comp);
}

template <typename RandomAccessIterator, typename Distance>
void _sort_heap(RandomAccessIterator _first, RandomAccessIterator _last,
                Distance*)
{
    if(_last - _first > 1)
    {
        for(Distance n = _last - _first; n > 1; --n, --_last)        
            wt::pop_heap(_first, _last);
    }
}

template <typename RandomAccessIterator>
inline void sort_heap(RandomAccessIterator _first, RandomAccessIterator _last)
{
    wt::_sort_heap(_first, _last, _DIFFERENCE_TYPE(_first));
}

template <typename RandomAccessIterator, typename Distance, typename Compare>
void _sort_heap(RandomAccessIterator _first, RandomAccessIterator _last,
                Distance*, Compare _comp)
{
    if(_last - _first > 1)
    {
        for(Distance n = _last - _first; n > 1; --n, --_last)
            wt::pop_heap(_first, _last, _comp);
    }
}

template <typename RandomAccessIterator, typename Compare>
inline void sort_heap(RandomAccessIterator _first, RandomAccessIterator _last,
                      Compare _comp)
{
    wt::_sort_heap(_first, _last, _DIFFERENCE_TYPE(_first), _comp);
}

template <typename RandomAccessIterator, typename Distance>
Distance _is_heap_until(RandomAccessIterator _first, Distance _n)
{
    Distance parent = 0;
    for(Distance child = 1; child < _n; ++child)    
    {
        if(*(_first + parent) < *(_first + child))
            return child;
        if((child & 1) == 0)
            ++parent;
    }
    return _n;
}

template <typename RandomAccessIterator, typename Distance, typename Compare>
Distance _is_heap_until(RandomAccessIterator _first, Distance _n, Compare _comp)
{
    Distance parent = 0;
    for(Distance child = 1; child < _n; ++child)
    {
        if(_comp(*(_first + parent), *(_first + child)))
            return child;
        if((child & 1) == 0)
            ++parent;
    }
    return _n;
}

template <typename RandomAccessIterator, typename Distance>
inline bool _is_heap(RandomAccessIterator _first, Distance _n)
{
    return wt::_is_heap_until(_first, _n) == _n;
}

template <typename RandomAccessIterator, typename Distance, typename Compare>
inline bool _is_heap(RandomAccessIterator _first, Distance _n, Compare _comp)
{
    return wt::_is_heap_until(_first, _n, _comp) == _n;
}

template <typename RandomAccessIterator>
inline RandomAccessIterator
is_heap_until(RandomAccessIterator _first, RandomAccessIterator _last)
{
    return _first + wt::_is_heap_until(_first, wt::distance(_first, _last));
}

template <typename RandomAccessIterator, typename Compare>
inline RandomAccessIterator
is_heap_until(RandomAccessIterator _first, RandomAccessIterator _last,
              Compare _comp)
{
    return _first + wt::_is_heap_until(_first, wt::distance(_first, _last),
                                       _comp);
}

template <typename RandomAccessIterator>
inline bool 
is_heap(RandomAccessIterator _first, RandomAccessIterator _last)
{
    return wt::is_heap_until(_first, _last) == _last;
}

template <typename RandomAccessIterator, typename Compare>
inline bool
is_heap(RandomAccessIterator _first, RandomAccessIterator _last, Compare _comp)
{
    return wt::is_heap_until(_first, _last, _comp) == _last;
}


} // namespace wt

#endif