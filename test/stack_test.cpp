#include "test.hpp"

#include "../stack.hpp"

TEST_CASE("stack test", "[stack]") {

    SECTION("construtor") {
        wt::allocator<int> alloc;
        wt::deque<int> d1;
        wt::stack<int> s1;
        wt::stack<int> s2(d1);
        wt::stack<int> s3(alloc);
        wt::stack<int> s4(d1, alloc);
        wt::stack<int> s5(s4);
    }

    SECTION("operations") {
        wt::stack<char> s1;
        s1.push('h');
        s1.push('x');
        s1.push('q');
        REQUIRE(s1.empty() == false);
        REQUIRE(s1.size() == 3);
        REQUIRE(s1.top() == 'q');
        s1.emplace('H');
        REQUIRE(s1.size() == 4);
        REQUIRE(s1.top() == 'H');
        s1.pop();
        s1.pop();
        REQUIRE(s1.size() == 2);
        REQUIRE(s1.top() == 'x');
        wt::stack<char> s2;
        REQUIRE(s2.empty() == true);
        s2.swap(s1);
        REQUIRE(s1.empty() == true);
        REQUIRE(s2.size() == 2);
        REQUIRE(s2.top() == 'x');
        s2.pop();
        REQUIRE(s2.size() == 1);
        REQUIRE(s2.top() == 'h');
        s2.pop();
        REQUIRE(s2.empty() == true);
    }

}