#define CATCH_CONFIG_MAIN

#include "../string.hpp"
#include "catch.hpp"


template <typename InputIt>
void print(InputIt _first, InputIt _last)
{
    int count = 0;
    for(;_first != _last; ++_first)
    {
        ++count;
        std::cout << *_first ;
    }
    std::cout << "\n size: " << count << std::endl;
}

void separate(const wt::string& info)
{
    std::cout << "-----";
    for(auto it = info.cbegin(); it != info.cend(); ++it)
        std::cout << *it ;
    std::cout << "-----" << std::endl;
}

TEST_CASE("string","[string]") {
    SECTION("char_traits") {
        char c1 = 'a', c2 = 'x';
        wt::char_traits<char>::assign(c1, 'y');
        REQUIRE(c1 == 'y');
        REQUIRE(wt::char_traits<char>::lt(c2, c1));
        REQUIRE((wt::char_traits<char>::compare("abc", "abc", 3) == 0));
        REQUIRE((wt::char_traits<char>::compare("abc", "xyz", 3) == -1));
        REQUIRE((wt::char_traits<char>::compare("abc", "abb", 3) == 1));
        REQUIRE((wt::char_traits<char>::length("abcdefg") == 7));
    }

    SECTION("_String_base") {
        auto alloc = wt::allocator<char>();
        wt::_String_base<char, wt::allocator<char>> str(alloc);
        REQUIRE(str.get_allocator() == alloc);
        str._allocate_block(10);
        str._deallocate_block();
    }

    SECTION("basic_string") {
        REQUIRE(wt::string::npos == static_cast<size_t>(-1));
        wt::string s1;
        s1.assign("hello");
        s1.push_back(',');
        s1.append("world");
        wt::string s2(s1);
        s2.append(s1.begin(), s1.end());
        for(auto it = s2.begin(); it != s2.end(); ++it)
            std::cout << *it;
        std::cout << std::endl;
        REQUIRE(s1.size() == 11);
        s1.pop_back();
        REQUIRE(s1.size() == 10);
    }

    SECTION("insert") {
        wt::string s1("hello");
        s1.insert(1, 5, 'a');
        print(s1.begin(), s1.end());
        s1.insert(s1.cend() - 1, 'b');
        print(s1.begin(), s1.end());
        const char* cstr = "fuck";
        s1.insert(0, cstr);
        print(s1.begin(), s1.end());
    }

    SECTION("swap") {
        separate("swap start");
        wt::string s1("hello");
        wt::string s2("wt");
        print(s1.begin(), s1.end());
        print(s2.begin(), s2.end());
        s1.swap(s2);
        print(s1.begin(), s1.end());
        print(s2.begin(), s2.end());
        s2.swap(s1);
        print(s1.begin(), s1.end());
        print(s2.begin(), s2.end());
        separate("swap finish");
    }

    SECTION("rfind") {
        wt::string s1("this is a string rfind test");
        wt::string s2("string");
        auto pos = s1.rfind(s2);
        REQUIRE(pos == 10);
        auto pos1 = s1.rfind(s2, 10);
        REQUIRE(pos == 10);
        auto pos2 = s1.rfind('t', 10);
        REQUIRE(pos2 == 0);
        auto pos3 = s1.rfind('r');
        REQUIRE(pos3 == 17);
        auto pos4 = s1.rfind('t');
        REQUIRE(pos4 == s1.size() - 1);
    }

    SECTION("find_first_of") {
        wt::string s1("this s a string find first of test");
        wt::string s2("foe");
        REQUIRE(s1.find_first_of(s2) == 16);
        REQUIRE(s1.find_first_of('o') == 27);
        REQUIRE(s1.find_first_of('o', 28) == wt::string::npos);
        REQUIRE(s1.find_first_of("find") == 2);
        REQUIRE(s1.find_first_of("string", 12, 3) == 23);
    }

    SECTION("find_first_not_of") {
        wt::string s1("find first not of test");
        wt::string s2("find ");
        REQUIRE(s1.find_first_not_of(s2) == 7);
        REQUIRE(s1.find_first_not_of("first ", 7) == 11);
        REQUIRE(s1.find_first_not_of("not of test", 11, 7) == 19);
    }

    SECTION("find_last_of") {
        wt::string s1("this is a find_last_of test");
        wt::string s2("test ");
        REQUIRE(s1.find_last_of(s2) == 26);
        REQUIRE(s1.find_last_of(s2, 21) == 18);
        REQUIRE(s1.find_last_of("i", 10) == 5);
    }

    SECTION("compare") {
        wt::string s1("abcdefg");
        wt::string s2("abcdefg");
        wt::string s3("abcdefgh");
        wt::string s4("aaaaaaa");
        REQUIRE(s1 == s2);
        REQUIRE(s1 < s3);
        REQUIRE(s1 > s4);
        REQUIRE(s1 >= "abcdefg");
        REQUIRE(s1 > "a");
        REQUIRE(s1 < "b");
        REQUIRE(s1 <= "abcdefgh");
    }
}
