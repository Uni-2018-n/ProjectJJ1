#include "../lib/include/catch2/catch.hpp"

#include "../src/forward_list.h"

using namespace simple;

TEST_CASE("Check if a new forward_list is empty.", "[empty_forward_list]")
{
	forward_list<int> empty_forward_list;
	REQUIRE(empty_forward_list.empty());
}

TEST_CASE("Add item to empty forward list.", "[add_item_to_empty]")
{
	forward_list<int> list;

	list.push_back(9);

	REQUIRE(list.front()->m_value == 9);
}

TEST_CASE("Add many items to forward list.", "[add_many_items]")
{
	forward_list<int> list;

	list.push_back(19);
	list.push_back(29);
	list.push_back(39);
	list.push_back(49);

	auto curr_value = list.front();

	REQUIRE(curr_value->m_value == 19);
	curr_value = curr_value->m_next;

	REQUIRE(curr_value->m_value == 29);
	curr_value = curr_value->m_next;

	REQUIRE(curr_value->m_value == 39);
	curr_value = curr_value->m_next;

	REQUIRE(curr_value->m_value == 49);
	curr_value = curr_value->m_next;

	REQUIRE(curr_value == nullptr);
}
