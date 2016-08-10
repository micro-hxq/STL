#include "test.hpp"

#include "../queue.hpp"

TEST_CASE("priority_queue test", "[priority_queue]") {

    SECTION("constructor") {
        wt::priority_queue<int> p1;
        wt::allocator<int> alloc;
        wt::deque<int> d1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        wt::less<int> cmp;
        wt::priority_queue<int, wt::deque<int>> p2(cmp, d1);
        REQUIRE(p2.size() == 9);
        wt::priority_queue<int, wt::deque<int>> p3(p2);
        wt::priority_queue<int, wt::deque<int>> p4(wt::move(p3));
        wt::priority_queue<int> p5(alloc);
        wt::priority_queue<int, wt::deque<int>> p6(p2, alloc);
        wt::priority_queue<int, wt::deque<int>> p7(wt::move(p4), alloc);
        wt::priority_queue<int, wt::deque<int>> p8(d1.begin(), d1.begin());
    }

    SECTION("Operations") {
        wt::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        wt::less<int> cmp;
        wt::priority_queue<int> p1(cmp, v1);
        REQUIRE(p1.empty() == false);
        REQUIRE(p1.size() == 10);
        REQUIRE(p1.top() == 10);
        p1.pop();
        for(int i = 9; i > 0; --i)
        {
            REQUIRE(p1.top() == i);
            p1.pop();
        }
        REQUIRE(p1.empty() == true);

        for(int i = 0; i < 10; ++i)
        {
            p1.push(i);
        }
        REQUIRE(p1.size() == 10);
        REQUIRE(p1.top() == 9);
        wt::priority_queue<std::string> p2;
        p2.push(std::string("aaaaa"));
        p2.push("bbbbb");
        p2.emplace(5, 'c');
        p2.emplace(10, 'd');
        p2.push("hello");
        p2.emplace("world");
        while(!p2.empty())
        {
            std::cout << p2.top() << " ";
            p2.pop();
        }
        std::cout << std::endl;

        wt::priority_queue<int> p3;

        REQUIRE(p1.empty() == false);
        REQUIRE(p3.empty() == true);
        wt::swap(p1, p3);
        REQUIRE(p1.empty() == true);
        REQUIRE(p3.empty() == false);
    }
}