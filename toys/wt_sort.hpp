//
// Created by WT on 2016/11/29.
//

#ifndef _WT_SORT_HPP_
#define _WT_SORT_HPP_

namespace wt {

//  Time Complexity:    O(N^2)
//  Space Complexity:   O(1)
template <typename RandomIter, typename Compare = wt::default_order_t<void>>
void
selection_sort(RandomIter first, RandomIter last, Compare comp = Compare())
{
    for(; first != last; ++first)
    {
        auto min_iter = first;
        for(auto cur = wt::next(first); cur != last; ++cur)
            min_iter = comp(*min_iter, *cur) ? min_iter : cur;
        wt::iter_swap(first, min_iter);
    }
}

//  suitable for the partial sorted sequence
//  Time Complexity:    O(N^2)
//  Space Complexity:   O(1)
template <typename RandomIter, typename Compare = wt::default_order_t<void>>
void
insertion_sort(RandomIter first, RandomIter last, Compare comp = Compare())
{
    if(first != last)
    {
        for(auto cur = first + 1; cur != last; ++cur)
        {
            auto val = *cur;
            auto prev = cur - 1;
            for(; prev != first - 1 && comp(val, *prev); --prev)
                *(prev + 1) = *prev;
            *(prev + 1) = val;
        }
    }
}

//  a variant of insertion sort
//  Time Complexity:    < O(N^2)
//  Space Complexity:   O(1)
template <typename RandomIter, typename Compare = wt::default_order_t<void>>
void
shell_sort(RandomIter first, RandomIter last, Compare comp = Compare())
{
    auto len = wt::distance(first, last);
    decltype(len) h = 1;
    while(h < len / 3)                  //  sequence formula: (3^k - 1) / 2
        h = 3 * h + 1;
    while(h >= 1)
    {
        for(auto i = h; i < len; ++i)
        {
            for(auto j = i; j >= h && comp(*(first + j), *(first + j - h)); j -= h)
                wt::iter_swap(first + j, first + j -h );
        }
        h /= 3;
    }
}

namespace detail {

//  auxiliary partition function of quick sort
template <typename RandomIter,  typename Compare>
RandomIter
partition(RandomIter first, RandomIter last, Compare comp)
{
    auto value = *(--last);
    for(auto cur = first; cur != last; ++cur)
    {
        if(!comp(value, *cur))
            wt::iter_swap(first++, cur);
    }
    wt::iter_swap(first, last);
    return first;
}

} // namespace detail

//  conventional quick sort
//  Time Complexity:    O(NlogN)    The Worst: O(N^2)
//  Space Complexity:   O(1)
template <typename RandomIter,  typename Compare = wt::default_order_t<void>>
void
quick_sort(RandomIter first, RandomIter last, Compare comp = Compare())
{
    if(last - first > 1)
    {
        RandomIter pivot = wt::detail::partition(first, last, comp);
        quick_sort(first, pivot, comp);
        quick_sort(pivot + 1, last, comp);
    }
}

namespace detail {

template <typename Index>
inline Index
parent(Index idx)
{
    return (idx - 1) / 2;
}

template <typename Index>
inline Index
left(Index idx)
{
    return 2 * idx + 1;
}

template <typename Index>
inline Index
right(Index idx)
{
    return 2 * (idx + 1);
}

template <typename RandomIter, typename Distance, typename Comp>
void
adjust_heap(RandomIter first, Distance n, Distance idx, Comp comp)
{
    Distance lc = left(idx), rc = right(idx), largest = 0;
    if(lc < n && comp(*(first + idx), *(first + lc)))
        largest = lc;
    else
        largest = idx;
    if(rc < n && comp(*(first + largest), *(first + rc)))
        largest = rc;
    if(largest != idx)
    {
        wt::iter_swap(first + idx, first + largest);
        adjust_heap(first, n, largest, comp);
    }
}

template <typename RandomIter, typename Comp>
inline void
make_heap(RandomIter first, RandomIter last, Comp comp)
{
    auto n = last - first;
    for(auto cur = parent(n - 1); cur >= 0; --cur)
        adjust_heap(first, n, cur, comp);
}

} // namespace detail

//  heap sort
//  Time Complexity:    O(NlogN)
//  Space Complexity:   O(1)
template <typename RandomIter, typename Comp = wt::default_order_t<void>>
void
heap_sort(RandomIter first, RandomIter last, Comp comp = Comp())
{
    if(first == last)
        return;
    detail::make_heap(first, last, comp);
    while(first != --last)
    {
        wt::iter_swap(first, last);
        detail::adjust_heap(first, last - first, 0, comp);
    }
}


template <typename RandomIter, typename Comp = wt::default_order_t<void>>
void
nth_element(RandomIter first, RandomIter nth, RandomIter last, Comp comp = Comp())
{
    if(last - first <= 1)
        return;
    auto pivot = detail::partition(first, last, comp);
    if(pivot == nth)
        return;
    if(pivot - nth > 0)
        nth_element(first, nth, pivot, comp);
    else
        nth_element(pivot, nth, last, comp);
}



} // namespace wt

#endif
