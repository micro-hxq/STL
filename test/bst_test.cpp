//
// Created by WT on 2017/2/7.
//

#include "test.hpp"
#include "../binary_search_tree.hpp"

TEST_CASE("bst_test", "[bst]") {
    SECTION("constructor") {
        wt::binary_search_tree<int, wt::allocator<int>> b1;
        wt::binary_search_tree<char> b2;
    }

    SECTION("insert erase min max") {
        wt::binary_search_tree<int> bst;
        CHECK(bst.empty());
        bst.insert(5);
        bst.insert(9);
        bst.insert(1);
        bst.insert(6);
        bst.insert(4);
        bst.insert(7);
        bst.insert(8);
        bst.insert(2);
        bst.insert(3);
        CHECK_FALSE(bst.empty());
        test::print(bst.begin(), bst.end(), "bst all");
        CHECK(bst.min() == 1);
        CHECK(bst.max() == 9);
        bst.erase(bst.search(9));
        CHECK(bst.max() == 8);
        bst.erase(bst.search(1));
        CHECK(bst.min() == 2);
        test::print(bst.begin(), bst.end(), "bst erase 9, 1");
        bst.erase(bst.search(5));
        test::print(bst.begin(), bst.end(), "bst erase 5");
        bst.clear();
        CHECK(bst.empty());
    }

    SECTION(" ") {
        wt::binary_search_tree<char> bst;
        CHECK(bst.empty());
        bst.insert('z');
        bst.insert('h');
        bst.insert('a');
        bst.insert('n');
        bst.insert('g');
        bst.insert('q');
        bst.insert('i');
        bst.insert('a');
        bst.insert('n');
        bst.insert('g');
        CHECK_FALSE(bst.empty());
        test::print(bst.cbegin(), bst.cend(), "zhangqiang");
    }
}