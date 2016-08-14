#include "test.hpp"

#include "../algorithm.hpp"
#include "../string.hpp"
#include "../vector.hpp"
#include "../functional.hpp"
#include "../forward_list.hpp"


TEST_CASE("algorithm", "[algorithm]") {

    SECTION("all_of") {

    } 

    SECTION("any_of") {

    }

    SECTION("none_of") {
        
    }

    SECTION("find") {

    }

    SECTION("search") {
        wt::string s1("this is a search test");
        wt::string s2("test");
        auto iter = wt::search(s1.begin(), s1.end(), s2.begin(), s2.end());
        REQUIRE(iter == s1.begin() + 17);
        auto iter2 = wt::search(s1.begin(), s1.end(), s2.begin(), s2.end(), wt::equal_to<void>());
        REQUIRE(iter2 == s1.begin() + 17);
        wt::vector<int> v1, v2;
        v1.push_back(2);
        v1.push_back(3);
        v1.push_back(1);
        v1.push_back(4);
        v2.push_back(3);
        v2.push_back(1);
        auto it1 = wt::search(v1.begin(), v1.end(), v2.begin(), v2.end());
        REQUIRE(it1 == (v1.begin() + 1));
        auto it2 = wt::search(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::equal_to<void>());
        REQUIRE(it2 == v1.begin() + 1);
    }

    SECTION("search_n") {
        wt::vector<int> v1 = {1, 2, 3, 4, 5, 3, 3, 3, 4, 3, 3, 3, 3, 8, 9};
        REQUIRE(wt::search_n(v1.begin(), v1.end(), 0, 1) == v1.begin());
        REQUIRE(wt::search_n(v1.begin(), v1.end(), 3, 3) == v1.begin() + 5);
        REQUIRE(wt::search_n(v1.begin(), v1.end(), 4, 3) == v1.end() - 6);

    }

    SECTION("find_end") {
        wt::string s1("this is a find_end test find_end test and find_end.");
        wt::string s2("find_end");
        auto it1 = wt::find_end(s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend());
        REQUIRE(it1 == s1.cbegin() + 42);
        auto it2 = wt::find_end(s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend(), wt::equal_to<void>());
        REQUIRE(it2 == s1.cbegin() + 42);
    }

    SECTION("rotate") {
        wt::vector<int> v1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto iter = wt::rotate(v1.begin(), v1.begin() + 4, v1.end());
        REQUIRE(*v1.begin() == 4);
        REQUIRE(*iter == 0);
    }

    SECTION("unique") {
        wt::vector<char> v1 = {'a', 'a', 'b', 'b', 'c', 'b', 'c', 'c', 'd'};
        wt::vector<char> v2 = v1;
        auto iter = wt::unique(v1.begin(), v1.end());
        test::print(v1.begin(), iter, "unique v1");
        REQUIRE(iter - v1.begin() == 6);
        test::print(v2.begin(), wt::unique(v2.begin(), v2.end(), wt::greater_equal<void>()), "unique v2");
    }

    SECTION("unique_copy") {

    }

    SECTION("partition") {
        wt::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto comp = [](int val) {   return val > 5; };
        REQUIRE(wt::is_partitioned(v1.begin(), v1.end(), comp) == false);
        auto iter = wt::partition(v1.begin(), v1.end(),comp);
        REQUIRE(wt::is_partitioned(v1.begin(), v1.end(), comp) == true);
        REQUIRE(iter == v1.begin() + 4);
        REQUIRE(iter == wt::partition_point(v1.begin(), v1.end(),comp));
        test::print(v1, "partition v1");

        wt::forward_list<int> f1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        REQUIRE(wt::is_partitioned(f1.begin(), f1.end(), comp) == false);
        auto iter2 = wt::partition(f1.begin(), f1.end(),comp);
        REQUIRE(wt::is_partitioned(f1.begin(), f1.end(), comp) == true);
        REQUIRE(*iter2 == 5);
        REQUIRE(iter2 == wt::partition_point(f1.begin(), f1.end(),comp));
        test::print(f1, "partition f1");
    }

    SECTION("partition_copy") {
        wt::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        wt::vector<int> v2, v3;
        wt::partition_copy(v1.begin(), v1.end(), wt::back_inserter(v2), wt::back_inserter(v3),
                           test::is_even<int>);
        test::print(v2, "partition_copy v2");
        test::print(v3, "partition_copy v3");
    }

    SECTION("stable_partition") {
        wt::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto comp = [](int val) {   return val > 5; };
        auto iter = wt::stable_partition(v1.begin(), v1.end(), comp, wt::less_time());
        REQUIRE(wt::is_partitioned(v1.begin(), v1.end(), comp) == true);
        REQUIRE(*iter == 1);
        REQUIRE(iter == wt::partition_point(v1.begin(), v1.end(), comp));
        test::print(v1, "stable_partition v1");

        wt::vector<int> v2 = {1, 5, 2, 6, 3, 7, 4, 8, 9};
        iter = wt::stable_partition(v2.begin(), v2.end(), comp, wt::less_space());
        REQUIRE(wt::is_partitioned(v2.begin(), v2.end(), comp) == true);
        REQUIRE(*iter == 1);
        REQUIRE(iter == wt::partition_point(v2.begin(), v2.end(), comp));
        test::print(v2, "stable_partition v2");

        wt::vector<int> v3 = {1, 11, 2, 12, 3, 13, 4, 14, 5, 15, 6, 16, 7, 17, 8, 9, 18, 19};
        auto comp3 = [](int val) {  return val > 10; };
        iter = wt::stable_partition(v3.begin(), v3.end(),comp3);
        REQUIRE(wt::is_partitioned(v3.begin(), v3.end(), comp3) == true);
        test::print(v3, "stable_partition v3");
    }

    SECTION("partial_sort") {
        wt::vector<int> v1 = {1, 5, 2, 6, 3, 7, 4, 8, 9};
        wt::partial_sort(v1.begin(), v1.begin() + 4, v1.end());
        REQUIRE(wt::is_sort(v1.begin(), v1.begin() + 4) == true);
        test::print(v1, "partial_sort v1");
    }

    SECTION("partial_sort_copy") {
        wt::vector<int> v1 = {1, 5, 2, 6, 3, 7, 4, 8, 9};
        wt::vector<int> v2(8);
        wt::vector<int> v3(20);
        auto iter1 = wt::partial_sort_copy(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::greater<void>());
        REQUIRE(iter1 == v2.end());
        REQUIRE(wt::is_sort(v2.begin(), iter1, wt::greater<void>()) == true);

        test::print(v2, "partial_sort_copy v2");
        auto iter2 = wt::partial_sort_copy(v1.begin(), v1.end(), v3.begin(), v3.end(), wt::greater<void>());
        REQUIRE(iter2 == v3.begin() + v1.size());
        REQUIRE(wt::is_sort(v3.begin(), iter2, wt::greater<void>()) == true);
        test::print(v3, "partial_sort_copy v3");

    }

    SECTION("binary search") {
        wt::vector<int> v1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        REQUIRE(wt::lower_bound(v1.begin(), v1.end(), 5) == v1.begin() + 5);
        REQUIRE(wt::lower_bound(v1.begin(), v1.end(), 8, wt::less<void>()) == v1.begin() + 8);

        REQUIRE(wt::upper_bound(v1.begin(), v1.end(), 5) == v1.begin() + 6);
        REQUIRE(wt::upper_bound(v1.begin(), v1.end(), 8, wt::less<int>()) == v1.begin() + 9);

        wt::vector<int> v2 = {0, 1, 2, 3, 3, 3, 4, 4, 5, 7, 8, 9};
        REQUIRE(wt::equal_range(v2.begin(), v2.end(), 3) == wt::make_pair(v2.begin() + 3, v2.begin() + 6));
        REQUIRE(wt::equal_range(v2.begin(), v2.end(), 4, wt::less<void>()) ==
                wt::make_pair(v2.begin() + 6, v2.begin() + 8));

        REQUIRE(wt::binary_search(v1.begin(), v1.end(), 4) == true);
        REQUIRE(wt::binary_search(v1.begin(), v1.end(), 10) == false);
        REQUIRE(wt::binary_search(v2.begin(), v2.end(), 5, wt::less<void>()) == true);
        REQUIRE(wt::binary_search(v2.begin(), v2.end(), 6, wt::less<void>()) == false);
    }

    SECTION("merge") {
        wt::vector<int> v1 = {0, 2, 4, 6, 8};
        wt::vector<int> v2 = {1, 3, 5, 7, 9, 10, 11, 12, 13, 14, 15};
        wt::vector<int> v3;
        wt::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::back_inserter(v3));
        test::print(v3, "merge v3");

        wt::vector<int> v4;
        wt::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::back_inserter(v4), wt::less<void>());
        test::print(v4, "merge v4");
    }

    SECTION("includes") {
        wt::vector<int> v1 = {0, 2, 4, 6, 8};
        wt::vector<int> v2 = {0, 4, 6};
        wt::vector<int> v3 = {0, 2, 4, 5, 8};
        REQUIRE(wt::includes(v1.begin(), v1.end(), v2.begin(), v2.end()) == true);
        REQUIRE(wt::includes(v1.begin(), v1.end(), v3.begin(), v3.end()) == false);
    }

    SECTION("set_difference") {
        wt::vector<int> v1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        wt::vector<int> v2 = {0, 2, 4, 6, 8};
        wt::vector<int> v3, v4;
        wt::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::back_inserter(v3));
        test::print(v3, "set_difference v3");

        wt::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::back_inserter(v4), 
                           wt::less<void>());
        test::print(v4, "set_difference v4");
    }

    SECTION("set_intersection") {
        wt::vector<int> v1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        wt::vector<int> v2 = {0, 0, 2, 4, 6, 8, 10};
        wt::vector<int> v3, v4;
        wt::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::back_inserter(v3));
        test::print(v3, "set_intersection v3");
        wt::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::back_inserter(v4),
                             wt::less<void>());
        test::print(v4, "set_intersection v4");
    }

    SECTION("set_symmetric_difference") {
        wt::vector<int> v1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        wt::vector<int> v2 = {0, 0, 2, 4, 6, 8, 10};
        wt::vector<int> v3, v4;
        wt::set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::back_inserter(v3));
        test::print(v3, "set_symmetric_difference v3");
        wt::set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::back_inserter(v4),
                                     wt::less<void>());
        test::print(v4, "set_symmetric_difference v4");
    }

    SECTION("set_union") {
        wt::vector<int> v1 = {0, 1, 2, 2, 3, 4, 5, 6, 7, 8, 8, 8, 9};
        wt::vector<int> v2 = {0, 0, 2, 4, 6, 6, 8, 10};
        wt::vector<int> v3, v4;
        wt::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::back_inserter(v3));
        test::print(v3, "set_union v3");
        wt::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::back_inserter(v4),
                      wt::less<void>());
        test::print(v4, "set_union v4");
    }
 
    SECTION("min and max") {
        REQUIRE(wt::min(10, 20) == 10);
        REQUIRE(wt::max(1, 2) == 2);
        REQUIRE(wt::min(10, 20, wt::greater<void>()) == 20);
        REQUIRE(wt::max(10, 20, wt::greater<void>()) == 10);
        REQUIRE(wt::min({1, 2, 3, 4}) == 1);
        REQUIRE(wt::max({1, 2, 3, 4}) == 4);
        REQUIRE(wt::minmax({1, 2, 3, 4}) == wt::make_pair(1, 4));
        wt::vector<int> v1 = {1, 1, 2, 3, 4, 4, 4, 3};
        REQUIRE(wt::minmax_element(v1.begin(), v1.end())== wt::make_pair(v1.begin(), v1.end() - 2));
    }

    SECTION("clamp") {
        REQUIRE(wt::clamp(9, 10, 20) == 10);
        REQUIRE(wt::clamp(10, 10, 20) == 10);
        REQUIRE(wt::clamp(11, 10, 20) == 11);
        REQUIRE(wt::clamp(19, 10, 20) == 19);
        REQUIRE(wt::clamp(20, 10, 20) == 20);
        REQUIRE(wt::clamp(21, 10, 20) == 20);
    }

    SECTION("is_permutation") {
        wt::vector<int> v1 = {1, 2, 3, 4, 5};
        wt::vector<int> v2 = {5, 4, 2, 3, 1};
        wt::vector<int> v3 = {2, 4, 5, 3, 2};
        wt::vector<int> v4 = {2, 1, 3, 5, 4, 6};
        REQUIRE(wt::is_permutation(v1.begin(), v1.end(), v2.begin()) == true);
        REQUIRE(wt::is_permutation(v1.begin(), v1.end(), v3.begin()) == false);
        REQUIRE(wt::is_permutation(v1.begin(), v1.end(), v4.begin()) == true);
        REQUIRE(wt::is_permutation(v1.begin(), v1.end(), v2.begin(), wt::equal_to<void>()) == true);
        REQUIRE(wt::is_permutation(v1.begin(), v1.end(), v3.begin(), wt::equal_to<void>()) == false);

        REQUIRE(wt::is_permutation(v1.begin(), v1.end(), v2.begin(), v2.end()) == true);
        REQUIRE(wt::is_permutation(v1.begin(), v1.end(), v3.begin(), v3.end()) == false);
        REQUIRE(wt::is_permutation(v1.begin(), v1.end(), v4.begin(), v4.end()) == false);
        REQUIRE(wt::is_permutation(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::equal_to<void>()) == true);
        REQUIRE(wt::is_permutation(v1.begin(), v1.end(), v3.begin(), v3.end(), wt::equal_to<void>()) == false);
    }

    SECTION("next_permutation") {
        std::string s1 = "abc";
        do {
            std::cout << s1 << std::endl;
        } while(wt::next_permutation(s1.begin(), s1.end()));

        do {
            std::cout << s1 << " <-" << std::endl;
        } while(wt::next_permutation(s1.begin(), s1.end(), wt::less<void>()));
    }

    SECTION("prev_permutation") {
        std::string s1 = "cba";
        do {
            std::cout << s1 << std::endl;
        } while(wt::prev_permutation(s1.begin(), s1.end()));
        do {
            std::cout << s1 << " <-" << std::endl;
        } while(wt::prev_permutation(s1.begin(), s1.end(), wt::less<void>()));
    }
}