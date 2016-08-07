#include "test.hpp"

#include "../forward_list.hpp"
#include "../vector.hpp"

TEST_CASE("forward_list test", "[forward_list]") {

    SECTION("fwd_list_base") {
        wt::allocator<int> alloc;
        wt::Fwd_list_base<int, wt::allocator<int>> fl1(alloc);
        wt::Fwd_list_base<int, wt::allocator<int>> fl2(fl1);
        REQUIRE(fl1.get_allocator() == alloc);
        REQUIRE(fl1.get_allocator() == fl2.get_allocator());
    }

    SECTION("constructor") {
        wt::allocator<char> alloc;
        wt::forward_list<char> f1;
        wt::forward_list<char> f2(alloc);
        wt::forward_list<char> f3(f1, alloc);
        wt::forward_list<char> f4(wt::move(f2));
        wt::forward_list<char> f5 = {'a', 'b', 'c'};
        test::print(f5, "initializer_list");
        wt::forward_list<char> f6(++f5.begin(), f5.end());
        test::print(f6, "range insert");
    }

    SECTION("operator=") {
        wt::forward_list<int> f1 = {1, 2, 3, 4, 5};
        wt::forward_list<int> f2 = {9, 8, 7 ,6};
        wt::forward_list<int> f3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        wt::forward_list<int> f4;
        f4 = {4, 2, 3};
        test::print(f4, "initializer_list");
        f4 = f1;
        test::print(f4, "copy assignment f1");
        f4 = f2;
        test::print(f4, "copy assignment f2");
        f4 = f3;
        test::print(f4, "copy assignment f3");
        f4 = wt::move(f1);
        test::print(f1, "f1");
        test::print(f4, "f4");
    }

    SECTION("assign") {
        wt::vector<char> v1 = {'a', 'b', 'c', 'd'};
        wt::forward_list<char> f1;
        f1.assign(10, 'x');
        test::print(f1, "10 x");
        f1.assign(v1.begin(), v1.end());
        test::print(f1, "first last");
        f1.assign({'A', 'B', 'C', 'X', 'Y', 'Z'});
        test::print(f1, "initializer_list");
    }

    SECTION("front") {
        wt::forward_list<int> f1{1, 2, 3, 4};
        REQUIRE(f1.front() == 1);
        f1.front() = 999;
        const auto f2 = f1;
        REQUIRE(f2.front() != 1);
        REQUIRE(f2.front() == 999);
        // f2.front() = 0;
    }

    SECTION("Iterator") {
        wt::forward_list<int> f1 = {1, 2, 3, 4};
        auto iter1 = f1.before_begin();
        REQUIRE(++iter1 == f1.begin());
        test::print(f1.begin(), f1.end(), "iterator");
        f1.insert_after(f1.begin(), 12);
        f1.insert_after(f1.cbefore_begin(), 0);
        test::print(f1.cbegin(), f1.cend(), "const_iterator");
    }

    SECTION("Capacity") {
        wt::forward_list<int> f1;
        REQUIRE(f1.empty() == true);
        f1.assign(100, 2);
        REQUIRE(f1.empty() == false);
        REQUIRE(f1.size() == 100);
        std::cout << "max_size: " << f1.max_size() << std::endl;
        f1.clear();
        REQUIRE(f1.size() == 0);
        REQUIRE(f1.empty() == true);
    }

    SECTION("insert_after") {
        wt::forward_list<char> f1 = {'w', 't'};
        f1.insert_after(++f1.begin(), 'f');
        f1.insert_after(f1.cbefore_begin(), 2, '*');
        f1.insert_after(f1.begin(), {'h', 'x', 'q'});
        wt::forward_list<char> f2(2, '*');
        f2.insert_after(f2.begin(), f1.begin(), f1.end());
        test::print(f1, "f1");
        test::print(f2, "f2");
    }

    SECTION("emplace_after") {
        wt::forward_list<std::string> f1{"hello", "world"};
        f1.emplace_after(f1.begin(), 10, '*');
        test::print(f1, "emplace_after f1");
    }

    SECTION("erase_after") {
        wt::forward_list<int> f1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        f1.erase_after(f1.begin());
        REQUIRE(*(++f1.begin()) == 3);
        auto first = ++f1.cbegin();
        auto last = first;
        wt::advance(last, 6);
        f1.erase_after(first, last);
        test::print(f1, "erase_after f1");
    }

    SECTION("push pop and emplace") {
        wt::forward_list<std::string> f1 = {"hello", "wt"};
        f1.push_front(std::string("=.="));
        f1.emplace_front(5, 'x');
        test::print(f1, "f1");
        f1.pop_front();
        test::print(f1, "pop_front f1");
    }

    SECTION("resize") {
        wt::forward_list<char> f1 = {'w', 't', 'h', 'x', 'q'};
        REQUIRE(f1.size() == 5);
        f1.resize(10);
        test::print(f1, "resize 10");
        f1.resize(2);
        test::print(f1, "resize 2");
        f1.resize(5);
        REQUIRE(f1.size() == 5);

        wt::forward_list<char> f2;
        f2.swap(f1);
        test::print(f2, "swap f2");
        REQUIRE(f1.empty() == true);
        wt::swap(f1, f2);
        REQUIRE(f2.empty() == true);
    }

    SECTION("Operations") {
        wt::forward_list<char> f1, f2;
        for(char c = 'a'; c <= 'z'; ++c)
        {
            f1.push_front(c);
            f2.push_front(c);
        }
        test::print(f1, "before sort f1");
        f1.sort();
        test::print(f1, "after sort f1");
        f2.reverse();
        REQUIRE(f1 == f2);
        f1.merge(f2);
        REQUIRE(f2.empty() == true);
        test::print(f1, "after merge");
        auto iter = f1.cbegin();
        wt::advance(iter, 25);
        f2.splice_after(f2.cbefore_begin(), f1, iter, f1.cend());
        test::print(f1,"after splice_after f1");
        test::print(f2, "after splice_after f2");
        f1.remove('g');
        test::print(f1, "remove g");
        f2.remove_if(test::is_even<char>);
        test::print(f2, "remove if");
        f1.unique();
        test::print(f1, "unique");
        f2.unique(test::binary_equal<char>);
        test::print(f2, "unique ");
    }

    SECTION("relation") {
        wt::forward_list<int> f1 = {1, 2, 3, 4, 5};
        auto f2 = f1;
        wt::forward_list<int> f3 = {1, 2, 2, 4, 5};
        wt::forward_list<int> f4 = {1, 3, 3, 4, 5};
        REQUIRE(f1 == f2);
        REQUIRE(f1 != f3);
        REQUIRE(f1 > f3);
        REQUIRE(f1 < f4);
        REQUIRE(f3 <= f4);
    }
}