#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../list.hpp"
#include "../string.hpp"

template <typename InputIt>
void print(InputIt _first, InputIt _last, const std::string& info)
{
    std::cout << "-----" << info << " start-----\n";
    for(; _first != _last; ++_first)
        std::cout << *_first << " ";
    std::cout << "\n-----" << info << " finish-----" << std::endl;
}
template <typename T>
bool binaryPred(const T& v1, const T& v2)
{
    return v1 == v2;
}

template <typename T>
bool comp_ascend(const T& v1, const T& v2)
{
    return v1 < v2;
}

template <typename T>
bool comp_descend(const T& v1, const T& v2)
{
    return v2 < v1;
}

TEST_CASE("list", "[list]") {

    SECTION("constructor") {
        wt::list<int> il1(5, 2);
        print(il1.begin(), il1.end(), "constructor il1");
    }

    SECTION("assign") {
        wt::list<char> l1;
        l1.assign(10, 'x');
        print(l1.begin(), l1.end(), "assign l1");
        wt::list<char> l2;
        l2.assign(l1.begin(), l1.end());
        print(l2.begin(), l2.end(), "assign l2");
    }

    SECTION("insert") {
        wt::list<int> il1;
        il1.insert(il1.begin(), 10, 3);
        REQUIRE(il1.size() == 10);
        print(il1.begin(),il1.end(), "il1");
    }   

    SECTION("emplace") {
        wt::list<wt::string> sl;
        sl.emplace(sl.begin(), "hello world");
        REQUIRE(*sl.begin() == "hello world");
        REQUIRE(sl.emplace_back("fuck") == "fuck");
        REQUIRE(sl.back() == "fuck");
        REQUIRE(sl.emplace_front("wt") == "wt");

        wt::list<int> il(3, 10);
        il.emplace(++il.begin(), 200);
        print(il.begin(), il.end(), "emplace il");
        REQUIRE(il.emplace_back(819) == 819);
        print(il.begin(), il.end(), "emplace_back il");
        REQUIRE(il.emplace_front(423) == 423);
    }

    SECTION("resize") {
        wt::list<int> il(2, 100);
        il.resize(10, 5);
        print(il.begin(), il.end(), "resize il");
        il.resize(3);
        print(il.begin(), il.end(), "resize il");
        il.resize(5);
        print(il.begin(), il.end(), "resize il");
    }

    SECTION("splice") {
        wt::list<int> l1, l2, l3, l4;
        l1.resize(10, 1);
        l2.resize(5, 2);
        l3.resize(10, 3);
        l4.resize(10, 4);
        l1.splice(++l1.begin(), l2);
        print(l1.begin(), l1.end(), "splice l1");
        print(l2.begin(), l2.end(), "splice l2");
        l1.splice(l1.begin(), l3, --l3.end());
        REQUIRE(l3.size() == 9);
        print(l1.begin(), l1.end(), "splice l1");
        l1.splice(l1.begin(), l4, ++l4.begin(), --l4.end());
        REQUIRE(l4.size() == 2);
        print(l1.begin(), l1.end(), "splice l1");
    }

    SECTION("unique") {
        wt::list<int> l1, l2, l3;
        l1.resize(2, 2);
        l2.resize(3, 3);
        l3.resize(4, 4);
        l1.splice(l1.end(), l2);
        l1.splice(l1.end(), l3);
        print(l1.begin(), l1.end(), "unique l1");
        l1.unique(binaryPred<int>);
        print(l1.begin(), l1.end(), "unique l1");
    }

    SECTION("merge") {
        wt::list<int> l1, l2;
        l1.resize(5, 123);
        l2.assign(5, 999);
        l2.insert(l2.begin(), 101);
        l1.merge(l2, comp_ascend<int>);
        print(l1.begin(), l1.end(), "merge l1");
    }

    SECTION("reverse") {
        wt::list<int> l1(1, 1);
        for(int i=2; i<10; ++i)
            l1.insert(l1.end(), i);
        print(l1.begin(), l1.end(), "before reverse");
        l1.reverse();
        print(l1.begin(), l1.end(), "after reverse");
    }

    SECTION("sort") {
        wt::list<int> l1;
        for(int i = 0; i < 100; ++i)
            l1.push_front(i);
        print(l1.begin(), l1.end(), "before sort");
        l1.sort(comp_descend<int>);
        print(l1.begin(), l1.end(), "after sort");
    }
}