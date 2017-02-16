//
// Created by WT on 2017/2/16.
//

#include "test.hpp"
#include "../avl_tree.hpp"

TEST_CASE("avl_tree", "[avl_tree]") {
    SECTION("constructor") {
        wt::avl_tree<int> at1;
        wt::avl_tree<int, wt::allocator<int>> at2;
        wt::avl_tree<char> at3(wt::allocator<char>());
        wt::allocator<char> alloc;
        CHECK(at1.get_allocator() == alloc);
        CHECK(at2.get_allocator() == alloc);
    }

    SECTION("interface") {
        wt::avl_tree<int> at;
        CHECK(at.empty());

        at.insert(3);
        at.insert(2);
        at.insert(1);
        at.insert(4);
        at.insert(5);
        at.insert(6);
        at.insert(7);
        at.insert(16);
        at.insert(15);
        at.insert(14);
        at.insert(13);
        at.insert(12);
        at.insert(11);
        at.insert(10);
        at.insert(8);
        at.insert(9);

        for(auto cur = at.cbegin(); cur != at.cend(); ++cur)
            std::cout << *cur << ": " << at.height(cur) << std::endl;

        test::print(at.cbegin(), at.cend(), "at");
        CHECK(at.height() == 5);
        CHECK(at.minimum() == 1);
        CHECK(at.maximum() == 16);
        at.erase(at.search(8));
        CHECK(at.height() == 5);
        test::print(at.begin(), at.end(), "at erase 8");
        at.erase(at.search(1));
        test::print(at.begin(), at.end(), "at erase 1");
        at.erase(at.search(3));
        at.erase(at.search(5));
        at.erase(at.search(2));
        at.erase(at.search(4));
        at.erase(at.search(6));
        at.erase(at.search(14));
        at.erase(at.search(16));
        CHECK(at.height() == 3);

        for(auto cur = at.cbegin(); cur != at.cend(); ++cur)
            std::cout << *cur << ": " << at.height(cur) << std::endl;

        at.clear();
        CHECK(at.height() == 0);
        CHECK(at.empty());
    }
}