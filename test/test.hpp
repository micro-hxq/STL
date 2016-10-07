#ifndef _TEST_HPP_
#define _TEST_HPP_

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

namespace test {

template <typename Container>
void print(const Container& container, const std::string& info)
{
    int count = 0;
    std::cout << "-----<" << info << " begin>-----\n";
    for(const auto& elem : container)
    {
        ++count;
        std::cout << elem << ' ';
    }
    std::cout << "\nsize: " << count << "\n-----<" << info << " end>-----" << std::endl;
}

template <typename InputIt>
void print(InputIt first, InputIt last, const std::string& info)
{
    std::cout << "-----<" << info << " begin>-----\n";
    for(; first != last; ++first)
        std::cout << *first << " ";
    std::cout << "\n-----<" << info << " end>-----" << std::endl;
}

template <typename InputIt>
void print_pair(InputIt first, InputIt last, const std::string& info)
{
    std::cout << "-----<" << info << " begin>-----\n";
    for(; first != last; ++first)
        std::cout << '[' << first->first << ", " << first->second << "] ";
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