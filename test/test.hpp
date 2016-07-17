#ifndef _TEST_HPP_
#define _TEST_HPP_

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

namespace test {

template <typename InputIt>
void print(InputIt _first, InputIt _last, const std::string& info)
{
    std::cout << "-----<" << info << " begin>-----\n";
    for(; _first != _last; ++_first)
        std::cout << *_first << " ";
    std::cout << "\n-----<" << info << " end>-----" << std::endl;
}
template <typename T>
bool binary_equal(const T& v1, const T& v2)
{
    return v1 == v2;
}

template <typename T>
bool comp_ascend(const T& v1, const T& v2)
{
    return v1 < v2;
}

template <typename T>
bool comp_descend(const T& v1, const T& v2)
{
    return v2 < v1;
}

template <typename Integer>
bool is_even(Integer value)
{
    return value % 2 == 0;
}

} // namespace test

#endif