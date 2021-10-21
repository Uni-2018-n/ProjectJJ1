#include "../lib/include/catch2/catch.hpp"

#include "../src/word.h"

#include <cstring>

TEST_CASE("Create a word.", "[create_word]") { word my_word("this is a word."); }

TEST_CASE("Test for equality of the word.", "[test_equality]")
{
	word word_1("this is a word.");
	word word_2("this is a word.");
	word word_3("this is another word.");

	REQUIRE(word_1 == word_2);
	REQUIRE(word_1 != word_3);
}
