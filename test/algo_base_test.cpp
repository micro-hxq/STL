#include "test.hpp"
#include "../algorithm.hpp"
#include "../vector.hpp"
#include "../list.hpp"
#include "../functional.hpp"

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

    SECTION("copy equal copy_n"){
        wt::vector<int> r1;
        wt::list<int> r2;
        int r3[1000];
        for(int i = 0; i < 1000; ++i)
        {
            r1.push_back(i);
            r2.push_back(1000 - i);
            r3[i] = 2 * i;
        }
        CHECK(r1.size() == 1000);
        CHECK(r2.size() == 1000);

        std::vector<int> v1(1000);
        CHECK(wt::copy(r1.cbegin(), r1.cend(), v1.begin()) == v1.end());
        CHECK(wt::equal(v1.begin(), v1.end(), r1.begin()));
        CHECK(wt::equal(v1.cbegin(), v1.cend(), r1.cbegin(), wt::equal_to<void>()));
        auto p1 = wt::copy_n(r1.cbegin(), 1000, v1.begin());
        CHECK((p1.first == r1.cend() && p1.second == v1.end()));
        CHECK(wt::equal(v1.begin(), v1.end(), r1.begin()));
        CHECK(wt::equal(v1.cbegin(), v1.cend(), r1.cbegin(), wt::equal_to<void>()));
        
        CHECK(wt::equal(r1.begin(), r1.end(), r1.begin(), r1.end()));
        CHECK(wt::equal(r1.begin(), r1.end(), r1.begin(), r1.end(), wt::equal_to<void>()));

        CHECK(wt::copy(r2.begin(), r2.end(), v1.begin()) == v1.end());
        CHECK(wt::equal(v1.begin(), v1.end(), r2.begin()));
        CHECK(wt::equal(v1.cbegin(), v1.cend(), r2.cbegin(), wt::equal_to<void>()));
        auto p2 = wt::copy_n(r2.cbegin(), 1000, v1.begin());
        CHECK((p2.first == r2.cend() && p2.second == v1.end()));
        CHECK(wt::equal(v1.begin(), v1.end(), r2.begin()));
        CHECK(wt::equal(v1.cbegin(), v1.cend(), r2.cbegin(), wt::equal_to<void>()));

        CHECK(wt::copy(r3, r3 + 1000, v1.begin()) == v1.end());
        CHECK(wt::equal(v1.begin(), v1.end(), r3));
        CHECK(wt::equal(v1.cbegin(), v1.cend(), r3, wt::equal_to<void>()));
    }
}