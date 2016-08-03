#include "test.hpp"

#include "../array.hpp"

TEST_CASE("array test", "[array]") {

    SECTION("Element Access") {
        wt::array<int, 5> a1 = {1, 2, 3};
        test::print(a1, "a1");
        wt::array<char, 6> a2 = {'h', 'x', 'q', '4', '2', '3'};
        test::print(a2, "a2");
        REQUIRE(a1.front() == 1);
        REQUIRE(a1.at(1) == 2);
        REQUIRE(a1.at(2) == 3);
        REQUIRE(a1[3] == 0);
        REQUIRE(a1.back() == 0);
        test::print(a1.data() + 1, a1.data() + 3, "data");
    }

    SECTION("Iterator") {
        wt::array<int, 10> a1 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        test::print(a1.begin(), a1.end(), "iterator");
        test::print(a1.cbegin(), a1.cend(), "const iterator");
        test::print(a1.rbegin(), a1.rend(), "reverse iterator");
        test::print(a1.crbegin(), a1.crend(), "const reverse iterator");
    }

    SECTION("Capacity") {
        wt::array<int, 5> a1;
        wt::array<int, 0> a2;
        REQUIRE(a1.empty() == false);
        REQUIRE(a1.size() == 5);
        REQUIRE(a1.max_size() == 5);
        REQUIRE(a2.empty() == true);
        REQUIRE(a2.size() == 0);
        REQUIRE(a2.max_size() == 0);
    }

    SECTION("Operations") {
        wt::array<int, 5> a1, a2;
        a1.fill(8);
        a2.fill(2);
        test::print(a1, "fill a1");
        test::print(a2, "fill a2");
        wt::swap(a1, a2);
        test::print(a1, "swap a1");
        test::print(a2, "swap a2"); 
        wt::array<int, 5> a3(a2);
        REQUIRE(a3 == a2);
        REQUIRE(a3 > a1);
        REQUIRE(a1 < a3);
    }

    SECTION("get") {
        wt::array<int, 10> a1 = {10, 9, 8, 7, 6};
        REQUIRE(wt::get<0>(a1) == 10);
        REQUIRE(wt::get<1>(a1) == 9);
        REQUIRE(wt::get<4>(a1) == 6);
        REQUIRE(wt::get<9>(a1) == 0);
    }
}