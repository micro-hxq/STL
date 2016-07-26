#include "../iterator.hpp"
#include <iostream>
#include <vector>
#include <deque>

int main(int argc, char const *argv[])
{
    std::vector<int> ivec1{11,12,13,14};
    std::vector<int> ivec2;
    
    auto it1 = ivec1.end();
    auto it2 = ivec1.begin() + 2;
    auto iter = wt::make_reverse_iterator(it1);

    for(int i=0;i<4;++i)
        std::cout << *(iter++) << std::endl;

    --iter;

    std::cout << *iter << std::endl;

    iter -= 1;
    std::cout << *iter << std::endl;

    std::cout << (iter == wt::make_reverse_iterator(it2)) << std::endl;

    std::cout << "---------back_inserter----------" << std::endl;
    auto back_iter = wt::back_inserter(ivec2);
    back_iter = 1990;
    *back_iter = 8;
    back_iter++ = 19;
    *back_iter++ = 1993;
    ++back_iter = 4;
    *++back_iter = 23;
    std::cout << "size: " << ivec2.size() << std::endl;
    for(auto elem : ivec2)
        std::cout << elem << ' ';

    std::cout << "\n---------front_inserter----------" << std::endl;

    std::deque<int> ivec3;
    auto iter_front = wt::front_inserter(ivec3);
    for(auto elem : ivec2)
        *(iter_front++) = elem;
    for(auto elem : ivec3)
        std::cout << elem << ' ';
    std::cout << std::endl;

    std::initializer_list<int> il = {1, 2, 3, 4, 5};
    std::cout << "il size: " << il.size() << std::endl;
    for(auto iter1 = wt::rbegin(il), iter2 = wt::rend(il); iter1 != iter2; ++iter1)
        std::cout << *iter1 << " ";
    std::cout << std::endl;

    int array[] = {10, 11, 12, 13, 14, 15};
    for(auto iter1 = wt::rbegin(array), iter2 = wt::rend(array); iter1 != iter2; ++iter1)
        std::cout << *iter1 << " ";
    std::cout << std::endl;

    for(auto iter1 = wt::begin(array), iter2 = wt::end(array); iter1 != iter2; ++iter1)
        std::cout << *iter1 << " ";
    std::cout << std::endl;
    /* code */
    return 0;
}