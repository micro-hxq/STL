#include "test.hpp"
#include "../list.hpp"
#include "../string.hpp"

using namespace test;

TEST_CASE("list", "[list]") {

    SECTION("constructor") {
        wt::list<int> l1;
        wt::allocator<int> alloc;
        wt::list<int> l2(alloc);
        REQUIRE(l1.get_allocator() == l2.get_allocator());
        wt::list<int> il1(5, 2);
        print(il1.begin(), il1.end(), "constructor il1");
        wt::list<int> l3(2, 1, alloc);
        wt::list<int> l4(il1.begin(), il1.end(), alloc);
        print(l4.begin(), l4.end(), "constructor l4");
        wt::list<int> l5(l4);
        REQUIRE(l4 == l5);
        wt::list<int> l6(wt::move(l5));
        REQUIRE(l4 == l6);
        wt::list<int> l7(wt::move(l6), alloc);
        REQUIRE(l4 == l7);
    }

    SECTION("operator=") {
        wt::list<char> l1, l2;
        for(char c = 'a'; c <= 'z'; ++c)
            l1.push_back(c);
        print(l1.begin(), l1.end(), "operator= l1");
        l2 = l1;
        REQUIRE(l1 == l2);
        wt::list<char> l3;
        l3 = wt::move(l2);
        REQUIRE(l1 == l3);
        REQUIRE(l1 != l2);
    }

    SECTION("front and back") {
        wt::list<int> l1;
        for(int i = 0; i < 10; ++i)
            l1.push_back(i);
        REQUIRE(l1.front() == 0);
        REQUIRE(l1.back() == 9);
        l1.front() = 100;
        l1.back() = 200;
        REQUIRE(l1.front() == 100);
        REQUIRE(l1.back() == 200);
        const wt::list<int> l2(l1);
        REQUIRE(l2.front() == 100);
        REQUIRE(l2.back() == 200);
    }

    SECTION("iterator") {
        wt::list<char> l1;
        for(char c = 'a'; c <= 'z'; ++c)
            l1.push_back(c);        
        print(l1.rbegin(), l1.rend(), "reverse_iterator l1");
        print(l1.crbegin(), l1.crend(), "const_reverse_iterator l1");
    }

    SECTION("empty size and max_size") {
        wt::list<int> l1;
        REQUIRE(l1.empty() == true);
        l1.push_back(10);
        REQUIRE(l1.empty() == false);
        REQUIRE(l1.size() == 1);
        l1.resize(1000000);
        REQUIRE(l1.size() == 1000000);
        REQUIRE(l1.max_size() == static_cast<unsigned long>(-1));
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
        auto iter = il1.begin();
        wt::advance(iter, 5);
        il1.insert(iter, 99999);
        print(il1.begin(), il1.end(), "insert il1");
        wt::list<int> l2;
        l2.insert(l2.begin(), ++il1.begin(), --il1.end());
        print(l2.cbegin(), l2.cend(), "insert il2");
    }   

    SECTION("erase") {
        wt::list<char> l1;
        for(char c = 'a'; c <= 'z'; ++c)
            l1.push_back(c);        
        auto iter = l1.begin();
        wt::advance(iter, 5);
        auto iter2 = iter++;
        iter2 = l1.erase(iter2);
        REQUIRE(iter == iter2);
        print(l1.cbegin(), l1.cend(), "erase l1");
        auto iter3 = l1.erase(iter, --l1.end());
        REQUIRE(*iter3 == l1.back());
        print(l1.cbegin(), l1.cend(), "erase l1");
        l1.clear();
        REQUIRE(l1.size() == 0);
        REQUIRE(l1.empty() == true);
    }

    SECTION("push and pop") {
        wt::list<char> l1;
        l1.push_back('x');
        l1.push_front('h');
        l1.push_back('q');
        print(l1.begin(), l1.end(), "push l1");
        l1.pop_front();
        l1.pop_back();
        REQUIRE(l1.size() == 1);
        REQUIRE(l1.front() == l1.back());
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

    SECTION("merge") {
        wt::list<int> l1, l2;
        l1.resize(5, 123);
        l2.assign(5, 999);
        l2.insert(l2.begin(), 101);
        l1.merge(l2, comp_ascend<int>);
        print(l1.begin(), l1.end(), "merge l1");
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

    SECTION("remove") {
        wt::list<int> l1;
        for(int i = 0; i < 10; ++i)
            l1.push_back(i);
        l1.remove(5);
        print(l1.cbegin(), l1.cend(), "remove l1");
        l1.remove_if(is_even<int>);
        print(l1.cbegin(), l1.cend(), "remove even l1");
    }

    SECTION("reverse") {
        wt::list<int> l1(1, 1);
        for(int i=2; i<10; ++i)
            l1.insert(l1.end(), i);
        print(l1.begin(), l1.end(), "before reverse");
        l1.reverse();
        print(l1.begin(), l1.end(), "after reverse");
    }

    SECTION("unique") {
        wt::list<int> l1, l2, l3;
        l1.resize(2, 2);
        l2.resize(3, 3);
        l3.resize(4, 4);
        l1.splice(l1.end(), l2);
        l1.splice(l1.end(), l3);
        print(l1.begin(), l1.end(), "unique l1");
        l1.unique(binary_equal<int>);
        print(l1.begin(), l1.end(), "unique l1");
    }

    SECTION("sort") {
        wt::list<int> l1;
        for(int i = 0; i < 100; ++i)
            l1.push_front(i);
        print(l1.begin(), l1.end(), "before sort");
        l1.sort(comp_descend<int>);
        print(l1.begin(), l1.end(), "after sort");
    }

    SECTION("operator< > <= >=") {
        wt::list<char> l1,l2,l3,l4;
        for(char c = 'a'; c <= 'z'; ++c)
            l1.push_back(c);
        l2 = l1;
        l2.front() = 'b';
        l3 = l1;
        l3.back() = 'a';
        REQUIRE(l1 != l2);
        REQUIRE(l1 < l2);
        REQUIRE(l1 <= l2);
        REQUIRE(l1 > l3);
        REQUIRE(l1 >= l3);
        l4 = l1;
        REQUIRE(l1 == l4);
        REQUIRE(l1 <= l4);
        REQUIRE(l1 >= l4);
    }
}