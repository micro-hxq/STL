#include "test.hpp"

#include "../queue.hpp"


TEST_CASE("queue test", "[queue]") {

    SECTION("constructor") {
        wt::allocator<int> alloc;
        wt::deque<int> d1;
        wt::queue<int> q1;
        wt::queue<int> q2(alloc);
        wt::queue<int> q3(d1);
        wt::queue<int> q4(d1, alloc);
        wt::queue<int> q5(q4);
        wt::queue<int> q6(wt::move(q5));
    }

    SECTION("operator=") {
        wt::deque<char> d1 = {'h', 'x', 'q'};
        wt::queue<char> q1(d1);
        wt::queue<char> q2;
        q2 = q1;
        REQUIRE(q1 == q2);
        wt::queue<char> q3;
        q3 = wt::move(q2);
        REQUIRE(q1 == q3);
        q2.swap(q3);
        REQUIRE(q1 == q2);
    }

    SECTION("Operations") {
        wt::deque<int> d1({4, 2, 3});
        wt::queue<int> q1(d1);
        REQUIRE(q1.empty() == false);
        REQUIRE(q1.size() == 3);
        REQUIRE(q1.front() == 4);
        REQUIRE(q1.back() == 3);
        q1.push(8);
        q1.push(1);
        q1.push(9);
        REQUIRE(q1.size() == 6);
        REQUIRE(q1.back() == 9);
        q1.emplace(999);
        REQUIRE(q1.size() == 7);
        REQUIRE(q1.back() == 999);
        q1.pop();
        REQUIRE(q1.size() == 6);
        REQUIRE(q1.front() == 2);
        q1.pop();
        q1.pop();
        REQUIRE(q1.size() == 4);
        REQUIRE(q1.front() == 8);
        q1.pop();
        q1.pop();
        q1.pop();
        REQUIRE(q1.front() == q1.back());
        q1.pop();
        REQUIRE(q1.empty() == true);
    }
}