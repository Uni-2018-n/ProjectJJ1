#include "../lib/include/catch2/catch.hpp"

#include "../src/entry.h"
#include "../src/string.h"

using simple::string;

TEST_CASE("Create an entry and test its members.", "[create_entry_test_members]")
{
	string my_string("this is a sentence.");

	entry my_entry(my_string, 5);

	REQUIRE(my_entry.m_word == my_string);
	REQUIRE(my_entry.m_matching_queries[0] == 5);
	REQUIRE(my_entry.m_matching_queries.size() == 1);
}

TEST_CASE("Add a query to an entry.", "[add_query_to_entry]")
{
	string my_string("this is a sentence.");

	entry my_entry(my_string, 5);

	my_entry.add_query(9);

	REQUIRE(my_entry.m_matching_queries[0] == 5);
	REQUIRE(my_entry.m_matching_queries[1] == 9);
	REQUIRE(my_entry.m_matching_queries.size() == 2);
}
