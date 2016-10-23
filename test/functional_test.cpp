#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../functional.hpp"

TEST_CASE("functional", "[functional]") {

    SECTION("Arithmetic") {
        REQUIRE(wt::plus<int>()(10, 20) == 30);
        REQUIRE(wt::plus<void>()(20, '\0') == 20);

        REQUIRE(wt::minus<int>()(10, 20) == -10);
        REQUIRE(wt::minus<void>()(10, 'a') == -87);

        REQUIRE(wt::multiplies<int>()(10, 20) == 200);
        REQUIRE(wt::multiplies<void>()(10, 'a') == 970);

        REQUIRE(wt::divides<int>()(10, 2) == 5);
        REQUIRE(wt::divides<void>()(194, 'a') == 2);

        REQUIRE(wt::modulus<int>()(10, 20) == 10);
        REQUIRE(wt::modulus<int>()(23, 10) == 3);
        REQUIRE(wt::modulus<void>()(23, 'a') == 23);

        REQUIRE(wt::negate<int>()(10) == -10);
        REQUIRE(wt::negate<void>()(200) == -200);
    }

    SECTION("Relation") {
        REQUIRE(wt::equal_to<void>()('a', 'a') == true);
        REQUIRE(wt::equal_to<void>()('b', 'c') == false);
        REQUIRE(wt::equal_to<void>()(10, 10) == true);
        REQUIRE(wt::equal_to<void>()(97, 'a') == true);

        REQUIRE(wt::not_equal_to<char>()('a', 'b') == true);
        REQUIRE(wt::not_equal_to<char>()('a', 'a') == false);
        REQUIRE(wt::not_equal_to<void>()(12, 23) == true);

        REQUIRE(wt::greater<char>()('a', 'b') == false);
        REQUIRE(wt::greater<char>()('b', 'a') == true);
        REQUIRE(wt::greater<void>()('a', 'a') == false);
        CHECK(wt::greater<void>()(20, 1));
        CHECK_FALSE(wt::greater<void>()(1, 20));

        CHECK(wt::less<int>()(1, 2));
        CHECK_FALSE(wt::less<int>()(2, 2));
        CHECK(wt::less<void>()(20, 100));
        CHECK_FALSE(wt::less<void>()(100, 100));

        CHECK(wt::greater_equal<float>()(10.0, 9.9));
        CHECK_FALSE(wt::greater_equal<float>()(10.0, 10.1));
        CHECK(wt::greater_equal<void>()(23, 23));
        CHECK_FALSE(wt::greater_equal<void>()(1, 10));

        CHECK(wt::less_equal<int>()(10, 11));
        CHECK(wt::less_equal<int>()(10, 10));
        CHECK_FALSE(wt::less<int>()(10, 9));
        CHECK(wt::less_equal<void>()(1.3, 1.4));
        CHECK(wt::less_equal<void>()(1.2, 1.2));
        CHECK_FALSE(wt::less_equal<void>()(1.3, 1.2));
    }

    SECTION("Logical") {
        CHECK(wt::logical_and<bool>()(true, true));
        CHECK_FALSE(wt::logical_and<bool>()(true, false));
        CHECK(wt::logical_and<void>()(1, 1));
        CHECK_FALSE(wt::logical_and<void>()(1, 0));

        CHECK(wt::logical_or<bool>()(true, false));
        CHECK_FALSE(wt::logical_and<bool>()(false, false));
        CHECK(wt::logical_or<void>()(1, 0));
        CHECK_FALSE(wt::logical_or<void>()(0, 0));

        CHECK(wt::logical_not<bool>()(false));
        CHECK_FALSE(wt::logical_not<bool>()(true));
        CHECK(wt::logical_not<void>()(0));
        CHECK_FALSE(wt::logical_not<void>()(1));
    }

    SECTION("Bitwise") {
        CHECK(wt::bit_and<int>()(0x1, 0x0) == 0x0);
        CHECK(wt::bit_and<int>()(0x11, 0x10) == 0x10);
        CHECK(wt::bit_and<void>()(0xff, 0x0) == 0x0);
        CHECK(wt::bit_and<void>()(0xff, 0xff) == 0xff);

        CHECK(wt::bit_or<char>()(0x02, 0x01) == 0x03);
        CHECK(wt::bit_or<void>()(0xf0, 0x0f) == 0xff);

        CHECK(wt::bit_xor<int>()(0xff, 0x0f) == 0xf0);
        CHECK(wt::bit_xor<void>()(0x00, 0xff) == 0xff);

        CHECK(wt::bit_not<short>()(0xff00) == 0x00ff);
        CHECK(wt::bit_not<char>()(0x00) == (char)0xff);
    }

    SECTION("default_order") {
        REQUIRE(wt::default_order_t<int>()(10, 2) == false);
        REQUIRE(wt::default_order_t<int>()(2, 10) == true);
        REQUIRE(wt::default_order_t<void>()(10, 'a') == true);
        REQUIRE(wt::default_order_t<void>()('a', 10) == false);
    }
}