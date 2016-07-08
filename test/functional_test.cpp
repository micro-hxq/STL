#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../functional.hpp"

TEST_CASE("functional", "[functional]") {
    SECTION("equal_to") {
        REQUIRE(wt::equal_to<void>()('a', 'a') == true);
        REQUIRE(wt::equal_to<void>()('b', 'c') == false);
        REQUIRE(wt::equal_to<void>()(10, 10) == true);
        REQUIRE(wt::equal_to<void>()(97, 'a') == true);
    }

    SECTION("not_equal_to") {
        REQUIRE(wt::not_equal_to<char>()('a', 'b') == true);
        REQUIRE(wt::not_equal_to<char>()('a', 'a') == false);
        REQUIRE(wt::not_equal_to<void>()(12, 23) == true);

    }
}