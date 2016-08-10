#include "test.hpp"

#include "../algorithm.hpp"
#include "../vector.hpp"
#include "../functional.hpp"

TEST_CASE("heap test", "[heap]") {

    SECTION("push_heap") {
        wt::vector<int> v1 = {10, 8, 6, 4, 2, 1};
        v1.push_back(9);
        wt::push_heap(v1.begin(), v1.end());
        test::print(v1, "v1 push_heap 6");
        v1.push_back(11);
        wt::push_heap(v1.begin(), v1.end());
        test::print(v1, "v1 push_heap 11");
        v1.push_back(100);
        wt::push_heap(v1.begin(), v1.end());
        test::print(v1, "v1 push_heap 100");
        REQUIRE(wt::is_heap(v1.begin(), v1.end()) == true);
        wt::vector<int> v2 = {1, 2, 3, 4, 5, 6};
        v2.push_back(1);
        wt::push_heap(v2.begin(), v2.end(), wt::greater<void>());
        test::print(v2, "v2");
    }

    SECTION("pop_heap") {
        wt::vector<int> v1 = {10, 8, 6, 4, 2, 1};
        for(auto iter = v1.end(); iter != v1.begin() + 1; --iter)
            wt::pop_heap(v1.begin(), iter);
        test::print(v1, "after 5 times pop_heap");

        wt::vector<int> v2 = {1, 2, 3, 4, 5, 6};
        for(auto iter = v2.end(); iter != v2.begin(); --iter)
            wt::pop_heap(v2.begin(), iter, wt::greater<void>());
        test::print(v2, "v2");
    }

    SECTION("make_heap") {
        wt::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        wt::make_heap(v1.begin(), v1.end());
        test::print(v1, "v1 make_heap");
        REQUIRE(wt::is_heap(v1.begin(), v1.end()) == true);
        wt::vector<int> v2 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        wt::make_heap(v2.begin(), v2.end(), wt::greater<int>());
        REQUIRE(wt::is_heap(v2.begin(), v2.end(), wt::greater<int>()) == true);
    }

    SECTION("is_heap_until") {
        wt::vector<int> v1 = {1, 2, 3, 4, 5, 2, 6};
        REQUIRE(wt::is_heap(v1.begin(), v1.end(), wt::greater<void>()) == false);
        REQUIRE(*(wt::is_heap_until(v1.begin(), v1.end(), wt::greater<void>())) == 2);
        auto iter1 = wt::is_heap_until(v1.begin(), v1.end(), wt::greater<void>());
        REQUIRE(iter1 == v1.begin() + 5);

        wt::vector<int> v2 = {9, 8, 7, 6, 10, 4, 3, 2, 1};
        REQUIRE(wt::is_heap(v2.begin(), v2.end()) == false);
        REQUIRE(wt::is_heap_until(v2.begin(), v2.end()) == v2.begin() + 4);
    }
}