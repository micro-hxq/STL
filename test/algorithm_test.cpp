#include "test.hpp"

#include "../algorithm.hpp"
#include "../string.hpp"
#include "../vector.hpp"
#include "../functional.hpp"
#include "../forward_list.hpp"
#include "../list.hpp"


TEST_CASE("algorithm", "[algorithm]") {

    SECTION("all_of any_of none_of") {
        wt::vector<int> v1(1000, 1);
        auto v2(v1);
        v2[500] = 0;
        CHECK(wt::all_of(v1.begin(), v1.end(), [](int elem) { return elem == 1; }));
        CHECK_FALSE(wt::all_of(v2.begin(), v2.end(), [](int elem) { return elem == 1; }));
        CHECK_FALSE(wt::any_of(v1.begin(), v1.end(), [](int elem) { return elem != 1; }));
        CHECK(wt::any_of(v2.begin(), v2.end(), [](int elem) { return elem != 1; }));
        CHECK(wt::none_of(v1.begin(), v1.end(), [](int elem) { return elem != 1; }));
        CHECK_FALSE(wt::none_of(v2.begin(), v2.end(), [](int elem) { return elem != 0; }));
    }

    SECTION("for_each for_each_n") {
        wt::vector<int> v1(1000);
        wt::for_each(v1.begin(), v1.end(), [](int& elem) { elem = 1; });
        CHECK(wt::all_of(v1.begin(), v1.end(), [](int elem) { return elem == 1; }));
        wt::for_each_n(v1.begin(), 1000, [](int& elem) { elem += 1; });
        CHECK(wt::all_of(v1.begin(), v1.end(), [](int elem) { return elem == 2; }));
    }

    SECTION("count count_if") {
        wt::vector<int> v1 = { 0, 1, 2, 3, 4, 5, 5, 5, 6, 7, 8, 9};
        CHECK(wt::count(v1.begin(), v1.end(), 5) == 3);
        CHECK(wt::count_if(v1.begin(), v1.end(), [](int elem) { return elem % 2 == 0; }) == 5);
    }

    SECTION("mismatch") {
        wt::vector<int> v1 = {10, 20 ,30 ,40 ,50, 60, 70, 80, 90, 100};
        wt::vector<int> v2 = {10, 20, 30, 40, 50, 60, 70, 8, 90, 100};
        CHECK(wt::mismatch(v1.begin(), v1.end(), v1.begin()) == wt::make_pair(v1.end(), v1.end()));
        CHECK(wt::mismatch(v1.begin(), v1.end(), v2.begin()) == wt::make_pair(v1.begin() + 7, v2.begin() + 7));
        CHECK(wt::mismatch(v1.begin(), v1.end(), v1.begin(), v1.end()) == wt::make_pair(v1.end(), v1.end()));
        CHECK(wt::mismatch(v1.begin(), v1.end(), v2.begin(), v2.end())
                    == wt::make_pair(v1.begin() + 7, v2.begin() + 7));
        CHECK(wt::mismatch(v1.begin(), v1.end(), v1.begin(), wt::equal_to<void>()) == wt::make_pair(v1.end(), v1.end()));
        CHECK(wt::mismatch(v1.begin(), v1.end(), v2.begin(), wt::equal_to<void>()) == wt::make_pair(v1.begin() + 7, v2.begin() + 7));
        CHECK(wt::mismatch(v1.begin(), v1.end(), v1.begin(), v1.end(), wt::equal_to<void>()) == wt::make_pair(v1.end(), v1.end()));
        CHECK(wt::mismatch(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::equal_to<void>())
                    == wt::make_pair(v1.begin() + 7, v2.begin() + 7));
    }

    SECTION("adjacent_find find  ") {
        wt::vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 8, 9, 8};
        CHECK(wt::adjacent_find(v1.begin(), v1.end()) == (v1.begin() + 7));
        CHECK(wt::adjacent_find(v1.begin(), v1.end(),
                                [](const auto& e1, const auto& e2) { return e2 < e1; }) == (v1.end()- 2));

        CHECK(wt::find(v1.begin(), v1.end(), 4) == v1.begin() + 3);
        CHECK(wt::find_if(v1.begin(), v1.end(), [](const auto& e) { return e == 4; }) == v1.begin() + 3);
        CHECK(wt::find_if_not(v1.begin(), v1.end(), [](const auto& e) { return e < 4; }) == v1.begin() + 3);

        wt::vector<int> sv = { 3, 4, 5};
        CHECK(wt::find_first_of(v1.begin(), v1.end(), sv.begin(), sv.end()) == v1.begin() + 2);
        CHECK(wt::find_first_of(v1.begin(), v1.end(), sv.begin(), sv.end(), wt::equal_to<void>()) == v1.begin() + 2);

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

        REQUIRE(wt::search_n(v1.begin(), v1.end(), 0, 1, wt::equal_to<void>()) == v1.begin());
        REQUIRE(wt::search_n(v1.begin(), v1.end(), 3, 3, wt::equal_to<void>()) == v1.begin() + 5);
        REQUIRE(wt::search_n(v1.begin(), v1.end(), 4, 3, wt::equal_to<void>()) == v1.end() - 6);

    }

    SECTION("find_end") {
        wt::string s1("this is a find_end test find_end test and find_end.");
        wt::string s2("find_end");
        auto it1 = wt::find_end(s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend());
        REQUIRE(it1 == s1.cbegin() + 42);
        auto it2 = wt::find_end(s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend(), wt::equal_to<void>());
        REQUIRE(it2 == s1.cbegin() + 42);
    }

    SECTION("swap_ranges swap") {
        wt::vector<int> v1(10, 1);
        wt::vector<int> v2(10, 9);
        CHECK(wt::swap_ranges(v1.begin(), v1.begin() + 5, v2.begin()) == v2.begin() + 5);
        test::print(v1.begin(), v1.end(), "swap_ranges v1");
        test::print(v2.begin(), v2.end(), "swap_ranges v2");
        int a[5] = {1, 2, 3, 4, 5};
        int b[5] = {5, 4, 3, 2, 1};
        test::print(wt::begin(a), wt::end(a), "swap a[5]");
        test::print(wt::begin(b), wt::end(b), "swap b[5]");
    }

    SECTION("copy_if") {
        wt::vector<int> v1 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        wt::vector<int> v2(5);
        auto iter = wt::copy_if(v1.begin(), v1.end(), v2.begin(), [](auto elem) { return elem % 2 == 1; });
        wt::vector<int> v3 {1, 3, 5, 7, 9};
        CHECK(iter == v2.end());
        CHECK(v2 == v3);
    }

    SECTION("move move_backward") {
        wt::vector<int> v1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        wt::vector<int> v2(10);
        auto iter = wt::move(v1.begin(), v1.begin() + 5, v2.begin());
        iter = wt::move_backward(v1.begin() + 5, v1.end(), v2.end());
        CHECK(iter == v2.begin() + 5);
        test::print(v2.begin(), v2.end(), "move v2");
    }

    SECTION("transform") {
        wt::vector<int> v1(10);
        auto pred = [](int elem) { return  1; };
        CHECK(wt::transform(v1.begin(), v1.end(), v1.begin(), pred) == v1.end());
        test::print(v1.begin(), v1.end(), "transform v1");
        auto p = [](int elem1, int elem2) { return elem1 + elem2; };
        CHECK(wt::transform(v1.begin(), v1.end(), v1.begin(), v1.begin(), p) == v1.end());
        test::print(v1.begin(), v1.end(), "transform v1");
    }

    SECTION("remove remove_if remove_copy remove_copy_if") {
        wt::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        wt::vector<int> v2,v3;
        wt::remove_copy(v1.begin(), v1.end(), wt::back_inserter(v2), 5);
        test::print(v2.begin(), v2.end(), "remove_copy v2");
        wt::remove_copy_if(v1.begin(), v1.end(), wt::back_inserter(v3), [](int elem) { return elem > 5; });
        test::print(v3.begin(), v3.end(), "remove_copy_if");
        CHECK(wt::remove(v1.begin(), v1.end(), 5) == v1.end() - 1);
        CHECK(wt::remove_if(v1.begin(), v1.end() - 1, [](int elem) { return elem < 5; }) == v1.begin() + 4);
        test::print(v1.begin(), v1.begin() + 4, "remove_if");
    }

    SECTION("replace replace_if replace_copy replace_copy_if") {
        wt::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        wt::vector<int> v2,v3;
        wt::replace_copy(v1.begin(), v1.end(), wt::back_inserter(v2), 5, 555);
        test::print(v2, "replace_copy");
        wt::replace_copy_if(v1.begin(), v1.end(), wt::back_inserter(v3), [](int elem) { return elem > 5; }, 0);
        test::print(v3, "replace_copy_if");
        wt::replace(v1.begin(), v1.end(), 5, 555);
        wt::replace_if(v1.begin(), v1.end(), [](int elem ) { return elem < 5; }, 0);
        test::print(v1, "replace");
    }

    SECTION("reverse reverse_copy") {
        wt::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        wt::vector<int> v2;
        wt::reverse(v1.begin(), v1.end());
        test::print(v1, "reverse");
        wt::reverse_copy(v1.begin(), v1.end(), wt::back_inserter(v2));
        test::print(v2, "reverse_copy");
    }

    SECTION("rotate rotate_copy") {
        wt::vector<int> v1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        wt::vector<int> v2;
        wt::rotate_copy(v1.begin(), v1.begin() + 4, v1.end(), wt::back_inserter(v2));
        auto iter = wt::rotate(v1.begin(), v1.begin() + 4, v1.end());
        REQUIRE(*v1.begin() == 4);
        REQUIRE(*iter == 0);
        CHECK(v1 == v2);
    }

    SECTION("unique unique_copy") {
        wt::vector<char> v1 = {'a', 'a', 'b', 'b', 'c', 'b', 'c', 'c', 'd'};
        wt::vector<char> v2 = v1;
        auto iter = wt::unique(v1.begin(), v1.end());
        test::print(v1.begin(), iter, "unique v1");
        REQUIRE(iter - v1.begin() == 6);
        test::print(v2.begin(), wt::unique(v2.begin(), v2.end(), wt::greater_equal<void>()), "unique v2");

        wt::vector<char> v3{'a', 'a', 'b', 'b', 'c', 'b', 'c', 'c', 'd'};
        wt::vector<char> v4, v5;
        wt::unique_copy(v3.begin(), v3.end(), wt::back_inserter(v4));
        test::print(v4, "unique_copy");
        wt::unique_copy(v3.begin(), v3.end(), wt::back_inserter(v5), wt::equal_to<void>());
        test::print(v5, "unique_copy");
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

    SECTION("lower_bound upper_bound equal_ranges binary search") {
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
        CHECK(wt::includes(v1.begin(), v1.end(), v2.begin(), v2.end()));
        CHECK(wt::includes(v1.begin(), v1.end(), v2.begin(), v2.end(), wt::less<void>()));
        CHECK_FALSE(wt::includes(v1.begin(), v1.end(), v3.begin(), v3.end()));
        CHECK_FALSE(wt::includes(v1.begin(), v1.end(), v3.begin(), v3.end(), wt::less<void>()));
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
        REQUIRE(((wt::minmax(1, 10).first == 1) && (wt::minmax(1, 10).second == 10)));
        REQUIRE(wt::minmax({1, 2, 3, 4}) == wt::make_pair(1, 4));
        wt::vector<int> v1 = {1, 1, 2, 3, 4, 4, 4, 3};
        REQUIRE(wt::minmax_element(v1.begin(), v1.end())== wt::make_pair(v1.begin(), v1.end() - 2));
        REQUIRE(wt::minmax_element(v1.begin(), v1.end(), wt::less<void>())== wt::make_pair(v1.begin(), v1.end() - 2));
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
        std::string s1 = "abcd";
        do {
            std::cout << s1 << std::endl;
        } while(wt::next_permutation(s1.begin(), s1.end()));

        do {
            std::cout << s1 << " <-" << std::endl;
        } while(wt::next_permutation(s1.begin(), s1.end(), wt::less<void>()));
    }

    SECTION("prev_permutation") {
        std::string s1 = "dcba";
        do {
            std::cout << s1 << std::endl;
        } while(wt::prev_permutation(s1.begin(), s1.end()));
        do {
            std::cout << s1 << " <-" << std::endl;
        } while(wt::prev_permutation(s1.begin(), s1.end(), wt::less<void>()));
    }
}