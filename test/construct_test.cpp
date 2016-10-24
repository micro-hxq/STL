#include <iostream>
#include <string>
#include "../allocator.hpp"
#include "../iterator.hpp"
struct _true_type{};
struct _false_type{};

template <typename T>
struct is_true : public _true_type {
    // is_true()
    // {
    //  std::cout << "is_true -> _true_type" <<std::endl;
    // }
};

template <>
struct is_true<int> : public _false_type
{
    // is_true()
    // {
    //  std::cout << "is_true<int> -> _false_type" << std::endl;
    // }
};
class Foo{};
void foo(_true_type)
{
    std::cout << "foo(_true_type)" << std::endl;
}

void foo(_false_type)
{
    std::cout << "foo(_false_type)" << std::endl;
}

void foo()
{
    foo(is_true<Foo>());
    foo(is_true<int>());
}


int main()
{
    foo();

    int i;
    float f;
    double d;
    std::string s;
    std::cout << "i: " << i << "\nf: " << f << "\ndouble: " << d 
                <<"\nstring: " << s << std::endl;

    wt::construct(&i);
    wt::construct(&f);
    wt::construct(&d);
    wt::construct(&s);

    std::cout << "after construct...\ni: " << i << "\nf: " << f << "\ndouble: " << d 
                <<"\nstring: " << s << std::endl;

}