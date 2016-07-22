#include "test.hpp"

#include "../deque.hpp"
#include "../vector.hpp"

TEST_CASE("deque_test", "[deque]") {
    SECTION("Deque_base") {
        wt::allocator<int> alloc;
        wt::Deque_base<int, wt::allocator<int>> db1(alloc);
        wt::Deque_base<int, wt::allocator<int>> db2(alloc, 1000);
        REQUIRE(db1.get_allocator() == alloc);
        REQUIRE(db1.get_allocator() == db2.get_allocator());
    }

    SECTION("deque constructor") {
        wt::deque<int> d1;
        wt::allocator<int> alloc;
        wt::deque<int> d2(alloc);
        REQUIRE(d1.get_allocator() == d2.get_allocator());
        wt::deque<char> d3(10, 'x');
        test::print(d3.begin(), d3.end(), "deque(count, value)");
        wt::deque<char> d4(d3.begin() + 1, d3.end() - 1);
        test::print(d4.begin(), d4.end(), "deque(begin, end)");
        wt::vector<int> v1(10, 9);
        wt::deque<int> d5(v1.begin(), v1.end());
        test::print(d5.begin(), d5.end(), "deque(begin, end) d5");
        wt::deque<char> d6(d3);
        REQUIRE(d6 == d3);
        wt::deque<char> d7(d3, alloc);
        REQUIRE(d7 == d3);
        wt::deque<char> d8(wt::move(d6));
        REQUIRE(d8 == d3);
        REQUIRE(d6 != d3);
        REQUIRE(d6.size() == 0);
        d6 = d3;
        REQUIRE(d6 == d3);
        d6.clear();
        d6 = wt::move(d8);
        REQUIRE(d8.empty() == true);
        REQUIRE(d6 == d3);
    }

    SECTION("assign") {
        wt::deque<char> d1;
        d1.assign(10, 'x');
        REQUIRE(d1.size() == 10);
        d1.assign(1000, 'z');
        REQUIRE(d1.size() == 1000);
        wt::deque<char> d2;
        d2.assign(d1.cbegin() + 20, d1.cend() - 20);
        REQUIRE(d2.size() == 960);
    }

    SECTION("Element Access") {
        wt::deque<char> d1(10, 'x');
        d1.push_back('z');
        d1.push_front('a');
        const wt::deque<char> d2(d1);
        REQUIRE(d1.at(0) == 'a');
        REQUIRE(d2.at(1) == 'x');
        REQUIRE_THROWS(d1.at(12));
        REQUIRE(d1[11] == 'z');
        REQUIRE(d2[10] == 'x');
        REQUIRE(d1.front() == 'a');
        REQUIRE(d1.back() == 'z');
        d1.front() = 'z';
        d1.back()  = 'a';
        REQUIRE(d1.front() == 'z');
        REQUIRE(d1.back() == 'a');
    }

    SECTION("Iterator") {
        wt::deque<char> d1;
        REQUIRE(d1.empty() == true);
        for(char c = 'A'; c <= 'Z'; ++c)
            d1.push_back(c);
        REQUIRE(d1.empty() == false);
        REQUIRE(d1.size() == 26);
        REQUIRE(*d1.begin() == 'A');
        REQUIRE(*d1.rbegin() == 'Z');
        REQUIRE(*(d1.crend() - 1) == 'A');
        test::print(d1.begin(), d1.end(), "iterator");
        test::print(d1.crbegin(), d1.crend(), "const reverse iterator");
        d1.clear();
        REQUIRE(d1.size() == 0);
        REQUIRE(d1.empty() == true);
    }

    SECTION("push and pop") {
        wt::deque<int> d1;
        d1.push_back(1);
        d1.push_back(2);
        d1.push_back(100);
        REQUIRE(d1.size() == 3);
        REQUIRE(d1.empty() == false);
        d1.pop_back();
        REQUIRE(d1.size() == 2);
        d1.pop_front();
        REQUIRE(d1.size() == 1);
        d1.clear();
        REQUIRE(d1.empty() == true);
    }

    SECTION("erase") {
        wt::deque<char> d1;
        for(char c = 'a'; c <= 'z'; ++c)
            d1.push_front(c);
        REQUIRE(d1.size() == 26);
        test::print(d1.begin(), d1.end(), "erase d1");
        d1.erase(d1.begin() + 5);
        d1.erase(d1.cbegin());
        d1.erase(d1.cend() - 1);
        REQUIRE(d1.size() == 23);
        test::print(d1.begin(), d1.end(), "erase d1");
        d1.erase(d1.begin() + 1, d1.end() - 1);
        test::print(d1.begin(), d1.end(), "erase d1");
    }

    SECTION("insert") {
        wt::deque<int> d1;
        d1.push_back(10);
        d1.push_back(11);
        d1.push_back(12);
        d1.push_back(13);
        auto iter = d1.insert(d1.begin() + 2, 999);
        REQUIRE(iter == d1.begin() + 2);
        iter = d1.insert(d1.begin(), 111);
        REQUIRE(iter == d1.begin());
        REQUIRE(d1.insert(d1.end(), 222) == d1.end());
        test::print(d1.begin(), d1.end(), "insert(pos, value) d1");
        iter = d1.insert(d1.begin() + 3, 200, 0);
        REQUIRE(iter == d1.begin() + 3);
        iter = d1.insert(d1.end() - 3, 200, 1);
        REQUIRE(iter == d1.end() - 203);
        test::print(d1.begin(), d1.end(), "insert(pos, count, value) d1");
        wt::deque<int> d2;
        d2.push_front(0);
        d2.push_front(0);
        d2.push_back(0);
        iter = d2.insert(d2.begin() + 1, d1.begin(), d1.end());
        REQUIRE(iter == d2.begin() + 1);
        iter = d2.insert(d2.begin(), d1.cbegin(), d1.cend());
        REQUIRE(iter == d2.begin());
        test::print(d2.begin(), d2.end(), "insert(pos, first, last) d2");
        wt::deque<int> d3(100, 7);
        iter = d2.insert(d2.end(), d3.begin(), d3.end());
        REQUIRE(iter == d2.end() - 100);
        iter = d2.insert(d2.end() - 101, d3.cbegin(), d3.cend());
        REQUIRE(iter == d2.end() - 201);
        test::print(d2.begin(), d2.end(), "insert(pos, first, last) d2 + d3");
    }

    SECTION("emplace") {
        wt::deque<std::string> d1;
        d1.emplace_front(10, 'z');
        d1.emplace_back(20, 'q');
        REQUIRE(d1.size() == 2);
        test::print(d1.cbegin(), d1.cend(), "emplace front and back");
        d1.emplace(d1.begin() + 1, 100, 'x');
        REQUIRE(d1.size() == 3);
        test::print(d1.cbegin(), d1.cend(), "emplace");
    }

    SECTION("resize") {
        wt::deque<char> d1(1000, 'Y');
        REQUIRE(d1.size() == 1000);
        d1.resize(10);
        REQUIRE(d1.size() == 10);
        d1.resize(15, 'A');
        REQUIRE(d1.size() == 15);
        test::print(d1.cbegin(), d1.cend(), "resize");
    }

    SECTION("relation operator") {
        wt::deque<int> d1(10, 2), d2(10, 2), d3(10, 3), d4(10, 1);
        REQUIRE(d1 == d2);
        REQUIRE(d2 != d4);
        REQUIRE(d1 < d3);
        REQUIRE(d1 > d4);
        REQUIRE(d2 <= d1);
        REQUIRE(d3 >= d2);
        d2.insert(d2.end(), 1);
        test::print(d1.begin(), d1.end(), "rel d1");
        test::print(d2.begin(), d2.end(), "rel d2");
        REQUIRE((d2 >= d1) == true);
    }
}
