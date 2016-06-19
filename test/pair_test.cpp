#define CATCH_CONFIG_MAIN

#include "../catch.hpp"

#include "../utility/wt_pair.hpp"

#include <string>

TEST_CASE("validate pair","[wt_pair]"){
    wt::pair<int,int> ip1(1,2), ip2(1,1), ip3(2,1), ip4(1,2);
    REQUIRE(ip1 > ip2);
    REQUIRE(ip1 < ip3);
    REQUIRE(ip1 == ip4);
    REQUIRE(ip2 <= ip3);
    REQUIRE(ip1 >= ip4);
    REQUIRE(ip1 <= ip4);
    REQUIRE(ip3 != ip4);

    wt::pair<float,double> dp(ip3);


    wt::pair<long,long> lp1, lp2(1,1), lp3(2,2);
    ip1 = lp2;
    REQUIRE(ip2 == ip1);

    wt::pair<std::string,std::string> sp1("hello","world"), sp3;
    auto sp0 = wt::make_pair<std::string,std::string>("hello","world");
    auto sp2 = wt::make_pair<const char*,const char*>("hello","world");
    sp3 = sp2;
    REQUIRE(sp0 == sp1);
}