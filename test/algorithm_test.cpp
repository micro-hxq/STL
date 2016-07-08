#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../algorithm.hpp"
#include "../string.hpp"
#include "../vector.hpp"
#include "../functional.hpp"

template <typename T>
bool eq_pred(const T& lhs, const T& rhs)
{
    return lhs == rhs;
}

TEST_CASE("algorithm", "[algorithm]") {
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

    SECTION("find_end") {
        wt::string s1("this is a find_end test find_end test and find_end.");
        wt::string s2("find_end");
        auto it1 = wt::find_end(s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend());
        REQUIRE(it1 == s1.cbegin() + 42);
        auto it2 = wt::find_end(s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend(), wt::equal_to<void>());
        REQUIRE(it2 == s1.cbegin() + 42);
    }
}