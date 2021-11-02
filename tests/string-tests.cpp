#include "../lib/include/catch2/catch.hpp"

#include "../src/string.h"

#include <cstring>

using bud::string;

TEST_CASE("Create a string.", "[create_string]") { string my_string("this is a string."); }

TEST_CASE("Test for equality of the string.", "[test_equality]")
{
	string word_1("this is a string.");
	string word_2("this is a string.");
	string word_3("this is another string.");

	REQUIRE(word_1 == word_2);
	REQUIRE(word_1 != word_3);
}

TEST_CASE("Copy strings.", "[copy_strings]")
{
	string word_1("this is a string.");
	string word_2 = word_1;
	REQUIRE(word_1 == word_2);
}

TEST_CASE("Self assignment string.", "[self_assignment_string]")
{
	string word_1("this is a string.");
	word_1 = word_1;
	REQUIRE(word_1 == word_1);
}

TEST_CASE("Check string character.", "[check_string_character]")
{
	string word_1("this is a string.");

	REQUIRE(word_1[1] == 'h');
}

TEST_CASE("Change string character.", "[change_string_character]")
{
	string word_1("this is a string.");

	word_1[1] = 'a';

	REQUIRE(word_1[1] == 'a');
}

TEST_CASE("Check copy constructor.", "[check_copy_constructor]")
{
	string word_1("this is a string.");

	string word_2 = word_1;

	REQUIRE(word_1 == word_2);
}

TEST_CASE("Check equal", "[check_equal]")
{
	string word_1("pp");
	string word_2("test");
	word_1 = word_2;
	REQUIRE(word_1 == word_2);
}

TEST_CASE("Check equal small", "[check_equal_small]")
{
	string word_1("pp");
	REQUIRE(word_1 == string("pp"));
}
