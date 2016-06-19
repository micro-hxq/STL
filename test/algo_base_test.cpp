#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../algorithm.hpp"
#include <vector>
#include <iostream>
#include <string>

TEST_CASE("algorithm","[algo_base]"){
    SECTION("swap"){
        bool b1 = false, b2 = true;
        REQUIRE((b1 == false && b2 == true));
        wt::swap(b1,b2);
        REQUIRE((b1 == true && b2 == false));

        std::vector<int> iv1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
        std::vector<int> iv2 = iv1;
        std::vector<int> iv3(10,100);

        REQUIRE(iv1 == iv2);
        for(auto b = iv2.begin(), e = iv2.end(), b2 = iv3.begin(); b != e; ++b, ++ b2)
            iter_swap(b, b2);
        for(auto b = iv2.begin(), e = iv2.end(); b != e; ++b)
            std::cout << *b << ' ';
        std::cout << std::endl;
        REQUIRE(iv1 == iv3);
    }

    SECTION("min and max"){
        int a = 1, b = 2;
        REQUIRE(wt::min(a, b) == 1);
        REQUIRE(wt::max(a, b) == 2);

        std::string s1 = "hello";
        std::string s2 = "heeld";
        REQUIRE(wt::min(s1, s2) == s2);
        REQUIRE(wt::max(s1, s2) == s1);

        auto reverse_lam = [](auto& lhs, auto& rhs){ return rhs < lhs; };
        REQUIRE(wt::min(a, b, reverse_lam) == b);
        REQUIRE(wt::max(a, b, reverse_lam) == a);
        REQUIRE(wt::min(s1, s2, reverse_lam) == s1);
        REQUIRE(wt::max(s1, s2, reverse_lam) == s2);

    }

    SECTION("copy"){
        
    }
}