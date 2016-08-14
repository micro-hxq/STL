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
    }

    SECTION("Relation") {
        REQUIRE(wt::equal_to<void>()('a', 'a') == true);
        REQUIRE(wt::equal_to<void>()('b', 'c') == false);
        REQUIRE(wt::equal_to<void>()(10, 10) == true);
        REQUIRE(wt::equal_to<void>()(97, 'a') == true);

        REQUIRE(wt::not_equal_to<char>()('a', 'b') == true);
        REQUIRE(wt::not_equal_to<char>()('a', 'a') == false);
        REQUIRE(wt::not_equal_to<void>()(12, 23) == true);
    }

    SECTION("Logical") {

    }

    SECTION("Bitwise") {

    }

    SECTION("default_order") {
        REQUIRE(wt::default_order_t<int>()(10, 2) == false);
        REQUIRE(wt::default_order_t<int>()(2, 10) == true);
        REQUIRE(wt::default_order_t<void>()(10, 'a') == true);
        REQUIRE(wt::default_order_t<void>()('a', 10) == false);
    }
}