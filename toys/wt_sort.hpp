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
        auto max_iter = first;
        for(auto cur = wt::next(first); cur != last; ++cur)
            max_iter = comp(*max_iter, *cur) ? max_iter : cur;
        wt::iter_swap(first, max_iter);
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



} // namespace wt

#endif
