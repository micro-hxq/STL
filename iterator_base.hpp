#ifndef _STL_WT_ITERATOR_BASE_HPP_
#define _STL_WT_ITERATOR_BASE_HPP_

namespace wt {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// template <typename Tp,typename Distance>
// struct input_iterator {
//     typedef input_iterator_tag  iterator_category;
//     typedef Tp                  value_type;
//     typedef Distance            difference_type;
//     typedef Tp*                 pointer;
//     typedef Tp&                 reference;
// };

// struct output_iterator {
//     typedef output_iterator_tag iterator_category;
//     typedef void                value_type;
//     typedef void                difference_type;
//     typedef void                pointer;
//     typedef void                reference;
// };

// template <typename Tp,typename Distance>
// struct forward_iterator {
//     typedef forward_iterator_tag    iterator_category;
//     typedef Tp                      value_type;
//     typedef Distance                difference_type;
//     typedef Tp*                     pointer;
//     typedef Tp&                     reference;
// };

// template <typename Tp,typename Distance>
// struct bidirectional_iterator{
//     typedef bidirectional_iterator_tag  iterator_category;
//     typedef Tp                          value_type;
//     typedef Distance                    difference_type;
//     typedef Tp*                         pointer;
//     typedef Tp&                         reference;
// };

// template <typename Tp,typename Distance>
// struct random_access_iterator{
//     typedef random_access_iterator_tag  iterator_category;
//     typedef Tp                          value_type;
//     typedef Distance                    difference_type;
//     typedef Tp*                         pointer;
//     typedef Tp&                         reference;
// };

template <typename Category, typename T, typename Distance = std::ptrdiff_t,
            typename Pointer = T*, typename Reference = T&>
struct iterator{
    typedef Category    iterator_category;
    typedef T           value_type;
    typedef Distance    difference_type;
    typedef Pointer     pointer;
    typedef Reference   reference;
};

template <typename Iterator>
struct iterator_traits{
    typedef typename Iterator::iterator_category    iterator_category;
    typedef typename Iterator::value_type           value_type;
    typedef typename Iterator::difference_type      difference_type;
    typedef typename Iterator::pointer              pointer;
    typedef typename Iterator::reference            reference;
};

template <typename T>
struct iterator_traits<T*>{
    typedef random_access_iterator_tag  iterator_category;
    typedef T                           value_type;
    typedef std::ptrdiff_t              difference_type;
    typedef T*                          pointer;
    typedef T&                          reference;
};


template <typename T>
struct iterator_traits<const T*>{
    typedef random_access_iterator_tag  iterator_category;
    typedef T                           value_type;
    typedef std::ptrdiff_t              difference_type;
    typedef const T*                    pointer;
    typedef const T&                    reference;
};

/**
 *  iterator operation
 */

//////////////
// distance //
//////////////

template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
_distance(InputIterator _first,InputIterator _last,input_iterator_tag)
{
    typename iterator_traits<InputIterator>::difference_type dist = 0;
    while(_first != _last)
    {
        ++_first;
        ++dist;
    }
    return dist;
}

template <typename RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
_distance(RandomAccessIterator _first,RandomAccessIterator _last,
            random_access_iterator_tag)
{
    return _last - _first;
}

template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator _first, InputIterator _last)
{
    using _IteratorCategory = typename iterator_traits<InputIterator>::iterator_category;
    return _distance(_first, _last, _IteratorCategory());
}

/////////////
// advance //
/////////////

template <typename InputIterator, typename Distance>
inline void _advance(InputIterator& _iter, Distance _n, input_iterator_tag)
{
    while(_n--)
    {
        ++_iter;
    }
}

template <typename BidirectionalIterator, typename Distance>
inline void _advance(BidirectionalIterator& _iter, Distance _n, bidirectional_iterator_tag)
{
    if(_n > 0)
    {
        while(_n--){ ++_iter; }
    }
    else
    {
        while(_n++){ --_iter; }
    }
}

template <typename RandomAccessIterator, typename Distance>
inline void _advance(RandomAccessIterator& _iter, Distance _n, random_access_iterator_tag)
{
    _iter += _n;
}

template <typename InputIterator, typename Distance>
inline void advance(InputIterator& _iter, Distance _n)
{
    using _IteratorCategory = typename iterator_traits<InputIterator>::iterator_category;
    _advance(_iter, _n, _IteratorCategory());
}

//////////
// next //
//////////

template <typename ForwardIterator>
inline ForwardIterator next(ForwardIterator _iter, 
                            typename iterator_traits<ForwardIterator>::difference_type _n = 1)
{
    auto tmp = _iter;
    advance(tmp,_n);
    return tmp;
}

//////////
// prev //
//////////

template <typename BidirectionalIterator>
inline BidirectionalIterator _prev(BidirectionalIterator _iter,
                        typename iterator_traits<BidirectionalIterator>::difference_type _n,
                        bidirectional_iterator_tag)
{
    while(_n--){ --_iter; }
    return _iter;
}                        

template <typename BidirectionalIterator>
inline BidirectionalIterator _prev(BidirectionalIterator _iter,
                        typename iterator_traits<BidirectionalIterator>::difference_type _n,
                        random_access_iterator_tag)
{
    return _iter -= _n;
}                        

template <typename BidirectionalIterator>
inline BidirectionalIterator prev(BidirectionalIterator _iter,
                        typename iterator_traits<BidirectionalIterator>::difference_type _n = 1)
{
    using _IteratorCategory = typename iterator_traits<BidirectionalIterator>::iterator_category;
    return _prev(_iter,_n,_IteratorCategory());
}

} // namespace wt
#endif