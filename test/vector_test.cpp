#define CATCH_CONFIG_MAIN

#include "../vector.hpp"

#include <iostream>
#include <string>
#include "catch.hpp"

template <typename Container>
void print(const Container& _container, const std::string& _info)
{
    int count = 0;
    std::cout << "----" << _info << "----start\n";
    for(const auto& elem : _container)
    {
        ++count;
        std::cout << elem << ' ';
    }
    std::cout << "\nsize: " << count << "\n----" << _info << "----end" << std::endl;
}

template <typename BidirectinoalIterator>
void print(BidirectinoalIterator _first, BidirectinoalIterator _last, const std::string& _info)
{
    int count = 0;
    std::cout << "----" << _info << "----start\n";
    for(; _first != _last; ++_first)
    {
        ++count;
        std::cout << *_first << " ";
    }

    std::cout << "\nsize: " << count << "\n----" << _info << "----end" << std::endl;
}

TEST_CASE("vector","[vector]") {
    SECTION("constructor") {
        wt::vector<int> v0;
        wt::vector<int> v1(10,1);
        wt::vector<int> v2(100);
        REQUIRE(v2.size() == 100);
        wt::vector<int> v3(v1);
        print(v3, "constructor");
        wt::vector<int> v5;
        v5 = v1;
        REQUIRE(v1 == v3);
        wt::vector<int> v4(v1.begin(), v1.end() - 1);
        REQUIRE(v4.size() == 9);
        REQUIRE(v1 != v4);
    }

    SECTION("iterator") {
        wt::vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        v.push_back(5);
        print(v, "iterator v");
        REQUIRE(v.size() == 5);
        auto iter = v.begin();
        REQUIRE(*iter++ == 1);
        REQUIRE(*++iter == 3);
        REQUIRE(*--iter == 2);
        REQUIRE(*iter-- == 2);
        REQUIRE(*iter == 1);
        REQUIRE(iter + 5 ==  v.end());
        REQUIRE(iter < v.end());
        REQUIRE(((iter <= iter) && (iter >= iter) && (iter == iter)));
        print(v.crbegin(), v.crend(), "reverse iterator");
    }

    SECTION("assign") {
        wt::vector<double> dv;
        dv.assign(20, 0.1);
        print(dv,"assign(count,value)");
        REQUIRE(dv.size() == 20);
        REQUIRE(dv.empty() == false);
        dv.push_back(0.5);
        wt::vector<double> dv2;
        dv2.assign(dv.rbegin(), dv.rend());
        REQUIRE(dv2.size() == 21);
        print(dv2, "assign(iterator)");
    }

    SECTION("capacity operation") {
        wt::vector<char> cv;
        REQUIRE(cv.empty() == true);
        for(char c = 'a'; c <='z'; ++c)
            cv.push_back(c);
        REQUIRE(cv.empty() == false);
        REQUIRE(cv.size() == 26);
        std::cout << "max size: " << cv.max_size() << std::endl;
        std::cout << "capacity: " << cv.capacity() << std::endl;
        cv.shrink_to_fit();
        REQUIRE(cv.size() == cv.capacity());
        cv.reserve(20);
        REQUIRE(cv.size() == 26);
        cv.reserve(100);
        REQUIRE(cv.capacity() == 100);
    }

    SECTION("element access") {
        wt::vector<float> fv;
        fv.push_back(0.1f);
        fv.push_back(0.2f);
        fv.push_back(0.3f);
        fv.push_back(0.4f);
        fv.push_back(0.5f);
        print(fv, "elememt access");
        REQUIRE(fv.front() == 0.1f);
        REQUIRE(fv[1] == 0.2f);
        REQUIRE(fv.at(2) == 0.3f);
        REQUIRE(fv[3] == 0.4f);
        REQUIRE(fv.back() == 0.5f);
        // fv.at(10) = 0.1f;
    }

    SECTION("modified operation") {
        wt::vector<int> iv;
        iv.assign(10,8);
        print(iv, "modified operation");
        iv.insert(iv.begin() + 5, 10);
        iv.insert(iv.end() - 1, 3, 100);
        print(iv,"insert 3 100");
        iv.insert(iv.end() - 2, iv.begin(), iv.begin() + 3);
        print(iv, "insert 3 8");
        iv.pop_back();
        REQUIRE(iv.size() == 16);
        print(iv, "after pop_back");
        iv.erase(iv.begin() + 5);
        print(iv, "after erase pos 5");
        auto iter = iv.erase(iv.begin(), iv.begin() + 9);
        print(iv, "after erase from 1 to 9");
        REQUIRE(iter == iv.begin());
        iv.resize(50, 50);
        REQUIRE(iv.size() == 50);
        iv.resize(10);
        REQUIRE(iv.size() == 10);
        print(iv, "after resize 10");
        iv.clear();
        REQUIRE(iv.size() == 0);
        REQUIRE(iv.empty() == true);
        REQUIRE(iv.capacity() != 0);
        wt::vector<char> cv1, cv2;
        cv1.assign(10, 'x');
        cv2.assign(5, 'o');
        print(cv1, "cv1");
        print(cv2, "cv2");
        cv1.swap(cv2);
        print(cv1, "cv1");
        print(cv2, "cv2");
        wt::swap(cv1, cv2);
        print(cv1, "cv1");
        print(cv2, "cv2");
    }
}