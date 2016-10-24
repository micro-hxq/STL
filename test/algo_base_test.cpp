#include "test.hpp"
#include "../algorithm.hpp"
#include "../vector.hpp"
#include "../list.hpp"
#include "../functional.hpp"

template <typename T>
void TEST_FILL(T val1, T val2)
{
    wt::vector<T> v1(10000);
    wt::fill(&v1[0], &v1[9999], val1);
    CHECK(wt::all_of(&v1[0], &v1[9999], [val1](T elem) { return elem == val1; }));
    CHECK((wt::fill_n(&v1[0], v1.size(), val2) == (&v1[9999] + 1)));
    CHECK(wt::all_of(&v1[0], &v1[9999], [val2](T elem) { return elem == val2; }));
}

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

    SECTION("copy equal copy_n copy_backwward"){
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

        wt::vector<int> r4(1000);
        CHECK(wt::copy_backward(r1.begin(), r1.end(), r4.end()) == r4.begin());
        CHECK(wt::equal(r1.begin() ,r1.end(), r4.begin(), r4.end()));
        CHECK(wt::copy_backward(r2.begin(), r2.end(), r4.end()) == r4.begin());
        CHECK(wt::equal(r2.begin(), r2.end(), r4.begin(), r4.end()));
    }

    SECTION("fill fill_n"){

        TEST_FILL<int>(6, 9);
        TEST_FILL<char>('z', 'q');
        TEST_FILL<unsigned char>('x', 'y');
        TEST_FILL<signed char>('A', 'B');
    }

    SECTION("lexicographical_compare lexicographical_compare_3way") {
        wt::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        wt::vector<int> v2{1, 2, 3, 4, 5, 6, 6, 8, 9, 10};
        wt::vector<int> v3{1 ,2 ,3, 5, 4, 2, 1, 2, 4, 1};

        CHECK_FALSE(wt::lexicographical_compare(v1.begin() ,v1.end(), v1.begin(), v1.end()));
        CHECK_FALSE(wt::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()));
        CHECK(wt::lexicographical_compare(v1.begin(), v1.end(), v3.begin(), v3.end()));
        CHECK_FALSE(wt::lexicographical_compare(v1.begin() ,v1.end(), v1.begin(), v1.end(), wt::less<void>()));
        CHECK_FALSE(wt::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::less<void>()));
        CHECK(wt::lexicographical_compare(v1.begin(), v1.end(), v3.begin(), v3.end(), wt::less<void>()));
        
        CHECK(wt::lexicographical_compare_3way(v1.begin() ,v1.end(), v1.begin(), v1.end()) == 0);
        CHECK(wt::lexicographical_compare_3way(v1.begin(), v1.end(), v2.begin(), v2.end()) == 1);
        CHECK(wt::lexicographical_compare_3way(v1.begin(), v1.end(), v3.begin(), v3.end()) == -1);
        CHECK(wt::lexicographical_compare_3way(v1.begin() ,v1.end(), v1.begin(), v1.end(), wt::less<void>()) == 0);
        CHECK(wt::lexicographical_compare_3way(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::less<void>()) == 1);
        CHECK(wt::lexicographical_compare_3way(v1.begin(), v1.end(), v3.begin(), v3.end(), wt::less<void>()) == -1);
    }
}