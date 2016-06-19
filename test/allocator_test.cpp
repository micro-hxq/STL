#include "allocator.hpp"

#include <iostream>
#include <vector>

template <typename T>
void sink_warn(const T&)
{
}

template <typename Container1, typename Container2>
void is_same(const Container1& c1, Container2)
{
    Container2 c2 = c1;
    sink_warn(c2);
}


int main(int argc, char const *argv[])
{
    
    std::vector<int,wt::allocator<int>> my_vec = {1,2,3,4};
    std::vector<double,
             wt::allocator_traits<wt::allocator<Foo>>::rebind_alloc<double>
                > my_double;

    is_same(my_vec,my_vec);

    for(auto elem : my_vec)
        std::cout << elem << ' ';
    // my_vec.reserve(100000004);
    for(int i=0;i<1000000;++i)
        my_vec.push_back(i);

    std::cout << "\nsize : " << my_vec.size() << std::endl;

    std::cout << "allocator : " << (my_vec.get_allocator() == my_double.get_allocator()) << std::endl;

}