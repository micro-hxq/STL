#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <string>
#include "type_traits.hpp"
// #include <type_traits>


class Foo{};

TEST_CASE("is_","[type_traits]"){
	SECTION("bool"){
		REQUIRE(wt::is_trivially_default_constructible<bool>::value == true);
		REQUIRE(wt::is_trivially_copy_constructible<bool>::value == true);
		REQUIRE(wt::is_trivially_move_constructible<bool>::value == true);
		REQUIRE(wt::is_trivially_copy_assignable<bool>::value == true);
		REQUIRE(wt::is_trivially_move_assignable<bool>::value == true);
		REQUIRE(wt::is_pod<bool>::value == true);
		REQUIRE(wt::is_integral<bool>::value == true);
	}

	SECTION("char"){
		REQUIRE(wt::is_trivially_default_constructible<char>::value == true);
		REQUIRE(wt::is_trivially_copy_constructible<char>::value == true);
		REQUIRE(wt::is_trivially_move_constructible<char>::value == true);
		REQUIRE(wt::is_trivially_copy_assignable<char>::value == true);
		REQUIRE(wt::is_trivially_move_assignable<char>::value == true);
		REQUIRE(wt::is_pod<char>::value == true);
		REQUIRE(wt::is_integral<char>::value == true);
	}

	SECTION("signed char"){
		REQUIRE(wt::is_trivially_default_constructible<signed char>::value == true);
		REQUIRE(wt::is_trivially_copy_constructible<signed char>::value == true);
		REQUIRE(wt::is_trivially_move_constructible<signed char>::value == true);
		REQUIRE(wt::is_trivially_copy_assignable<signed char>::value == true);
		REQUIRE(wt::is_trivially_move_assignable<signed char>::value == true);
		REQUIRE(wt::is_pod<signed char>::value == true);
		REQUIRE(wt::is_integral<signed char>::value == true);
	}

	SECTION("unsigned char"){
		REQUIRE(wt::is_trivially_default_constructible<unsigned char>::value == true);
		REQUIRE(wt::is_trivially_copy_constructible<unsigned char>::value == true);
		REQUIRE(wt::is_trivially_move_constructible<unsigned char>::value == true);
		REQUIRE(wt::is_trivially_copy_assignable<unsigned char>::value == true);
		REQUIRE(wt::is_trivially_move_assignable<unsigned char>::value == true);
		REQUIRE(wt::is_pod<unsigned char>::value == true);
		REQUIRE(wt::is_integral<unsigned char>::value == true);
	}

	SECTION("wchar_t"){
		REQUIRE(wt::is_trivially_default_constructible<wchar_t>::value == true);
		REQUIRE(wt::is_trivially_copy_constructible<wchar_t>::value == true);
		REQUIRE(wt::is_trivially_move_constructible<wchar_t>::value == true);
		REQUIRE(wt::is_trivially_copy_assignable<wchar_t>::value == true);
		REQUIRE(wt::is_trivially_move_assignable<wchar_t>::value == true);
		REQUIRE(wt::is_pod<wchar_t>::value == true);
		REQUIRE(wt::is_integral<wchar_t>::value == true);
	}

	SECTION("short"){
		REQUIRE(wt::is_trivially_default_constructible<short>::value == true);
		REQUIRE(wt::is_trivially_copy_constructible<short>::value == true);
		REQUIRE(wt::is_trivially_move_constructible<short>::value == true);
		REQUIRE(wt::is_trivially_copy_assignable<short>::value == true);
		REQUIRE(wt::is_trivially_move_assignable<short>::value == true);
		REQUIRE(wt::is_pod<short>::value == true);
		REQUIRE(wt::is_integral<short>::value == true);
	}

	SECTION("int"){
		REQUIRE(wt::is_trivially_default_constructible<int>::value == true);
		REQUIRE(wt::is_trivially_copy_constructible<int>::value == true);
		REQUIRE(wt::is_trivially_move_constructible<int>::value == true);
		REQUIRE(wt::is_trivially_copy_assignable<int>::value == true);
		REQUIRE(wt::is_trivially_move_assignable<int>::value == true);
		REQUIRE(wt::is_pod<int>::value == true);
		REQUIRE(wt::is_integral<int>::value == true);
	}

	SECTION("long"){
		REQUIRE(wt::is_trivially_default_constructible<long>::value == true);
		REQUIRE(wt::is_trivially_copy_constructible<long>::value == true);
		REQUIRE(wt::is_trivially_move_constructible<long>::value == true);
		REQUIRE(wt::is_trivially_copy_assignable<long>::value == true);
		REQUIRE(wt::is_trivially_move_assignable<long>::value == true);
		REQUIRE(wt::is_pod<long>::value == true);
		REQUIRE(wt::is_integral<long>::value == true);
	}

	SECTION("float"){
		REQUIRE(wt::is_trivially_default_constructible<float>::value == true);
		REQUIRE(wt::is_trivially_copy_constructible<float>::value == true);
		REQUIRE(wt::is_trivially_move_constructible<float>::value == true);
		REQUIRE(wt::is_trivially_copy_assignable<float>::value == true);
		REQUIRE(wt::is_trivially_move_assignable<float>::value == true);
		REQUIRE(wt::is_pod<float>::value == true);
		REQUIRE(wt::is_integral<float>::value == false);
	}

	SECTION("double"){
		REQUIRE(wt::is_trivially_default_constructible<double>::value == true);
		REQUIRE(wt::is_trivially_copy_constructible<double>::value == true);
		REQUIRE(wt::is_trivially_move_constructible<double>::value == true);
		REQUIRE(wt::is_trivially_copy_assignable<double>::value == true);
		REQUIRE(wt::is_trivially_move_assignable<double>::value == true);
		REQUIRE(wt::is_pod<double>::value == true);
		REQUIRE(wt::is_integral<double>::value == false);
	}

	SECTION("char*"){
		REQUIRE(wt::is_trivially_default_constructible<char*>::value == true);
		REQUIRE(wt::is_trivially_copy_constructible<char*>::value == true);
		REQUIRE(wt::is_trivially_move_constructible<char*>::value == true);
		REQUIRE(wt::is_trivially_copy_assignable<char*>::value == true);
		REQUIRE(wt::is_trivially_move_assignable<char*>::value == true);
		REQUIRE(wt::is_pod<char*>::value == true);
		REQUIRE(wt::is_integral<char*>::value == false);
	}

	SECTION("Foo"){
		CHECK(wt::is_trivially_default_constructible<Foo>::value == false);
		CHECK(wt::is_trivially_copy_constructible<Foo>::value == false);
		CHECK(wt::is_trivially_move_constructible<Foo>::value == false);
		CHECK(wt::is_trivially_copy_assignable<Foo>::value == false);
		CHECK(wt::is_trivially_move_assignable<Foo>::value == false);
		CHECK(wt::is_pod<Foo>::value == false);
		CHECK(wt::is_integral<Foo>::value == false);
	}

	SECTION("wt::string"){
		REQUIRE(wt::is_trivially_default_constructible<std::string>::value == false);
		REQUIRE(wt::is_trivially_copy_constructible<std::string>::value == false);
		REQUIRE(wt::is_trivially_move_constructible<std::string>::value == false);
		REQUIRE(wt::is_trivially_copy_assignable<std::string>::value == false);
		REQUIRE(wt::is_trivially_move_assignable<std::string>::value == false);
		REQUIRE(wt::is_pod<std::string>::value == false);
		REQUIRE(wt::is_integral<std::string>::value == false);
	}
}