#include "../type_traits.hpp"
#include "../algorithm.hpp"
#include "../iterator.hpp"
#include "../algorithm/wt_uninitialized.hpp"

#include <vector>
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    std::vector<int> iv1 = {1, 2, 3, 4, 5};
    std::vector<int> iv2(5);

    wt::uninitialized_copy(&*iv1.begin(), &*iv1.end(), &*iv2.begin());
    
    for(auto elem : iv2)
        std::cout << elem << " ";
    std::cout << std::endl;

    wt::uninitialized_fill(&*iv2.begin(), &*iv2.end(), 100);
    
    for(auto elem : iv2)
        std::cout << elem << " ";
    std::cout << std::endl;

    std::vector<std::string> iv3 = {"hello", " world"};
    std::vector<std::string> iv4(2);

    wt::uninitialized_copy(&*iv3.begin(), &*iv3.end(), &*iv4.begin());

    for(const auto& elem : iv4)
        std::cout << elem << " ";
    std::cout << std::endl;

    wt::uninitialized_fill(&*iv4.begin(), &*iv4.end(), "fuck");
    
    for(auto elem : iv4)
        std::cout << elem << " ";
    std::cout << std::endl;
    return 0;
}