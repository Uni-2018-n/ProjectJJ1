#include "../lib/include/catch2/catch.hpp"

#include "../src/unordered_map.h"

using namespace simple;

auto test_hash_function = [](std::size_t value) { return value; };

TEST_CASE("Search for items in empty map.", "[search_in_empty_map]")
{
	unordered_map<int, char, decltype(test_hash_function)> my_map(5, test_hash_function);

	REQUIRE(my_map[1] == nullptr);
	REQUIRE(my_map[2345] == nullptr);
	REQUIRE(my_map[93] == nullptr);
	REQUIRE(my_map[0] == nullptr);
	REQUIRE(my_map[231] == nullptr);
	REQUIRE(my_map[2] == nullptr);
	REQUIRE(my_map[3] == nullptr);
}

TEST_CASE("Insert items to unordered_map.", "[insert_to_unordered_map]")
{
	unordered_map<int, char, decltype(test_hash_function)> my_map(5, test_hash_function);

	my_map.insert(make_pair(1, 'a'));
	my_map.insert(make_pair(2, 'b'));
	my_map.insert(make_pair(3, 'c'));
	my_map.insert(make_pair(4, 'd'));
	my_map.insert(make_pair(5, 'e'));
	my_map.insert(make_pair(6, 'f'));
	my_map.insert(make_pair(7, 'g'));

	REQUIRE(*my_map[1] == 'a');
	REQUIRE(*my_map[2] == 'b');
	REQUIRE(*my_map[3] == 'c');
	REQUIRE(*my_map[4] == 'd');
	REQUIRE(*my_map[5] == 'e');
	REQUIRE(*my_map[6] == 'f');
	REQUIRE(*my_map[7] == 'g');
}

TEST_CASE("Modify value inserted to unordered map.", "[modify_value_inserted_to_map]")
{
	unordered_map<int, char, decltype(test_hash_function)> my_map(1, test_hash_function);

	my_map.insert(make_pair(99, 'a'));
	my_map.insert(make_pair(0, 'b'));

	*my_map[99] = 'y';
	*my_map[0] = 'z';

	REQUIRE(*my_map[99] == 'y');
	REQUIRE(*my_map[0] == 'z');

	*my_map[99] = 'o';
	REQUIRE(*my_map[99] == 'o');
}

TEST_CASE("Store many items in one unordered map list.", "[multiple_items_one_unordered_map_list]")
{
	unordered_map<int, char, decltype(test_hash_function)> my_map(1, test_hash_function);

	my_map.insert(make_pair(54, 'a'));
	my_map.insert(make_pair(99, 'b'));
	my_map.insert(make_pair(18, 'c'));
	my_map.insert(make_pair(60, 'd'));

	REQUIRE(*my_map[54] == 'a');
	REQUIRE(*my_map[99] == 'b');
	REQUIRE(*my_map[18] == 'c');
	REQUIRE(*my_map[60] == 'd');
}

TEST_CASE("Try to find non existing item.", "[find_non_existing_item]")
{
	unordered_map<int, char, decltype(test_hash_function)> my_map(2, test_hash_function);

	my_map.insert(make_pair(54, 'a'));
	my_map.insert(make_pair(99, 'b'));
	my_map.insert(make_pair(18, 'c'));
	my_map.insert(make_pair(60, 'd'));

	REQUIRE(my_map[53] == nullptr);
	REQUIRE(my_map[23] == nullptr);
	REQUIRE(my_map[0] == nullptr);
	REQUIRE(my_map[999] == nullptr);
	REQUIRE(my_map[111] == nullptr);
}

TEST_CASE("Insert existing key.", "[insert_existing_key]")
{
	unordered_map<int, char, decltype(test_hash_function)> my_map(2, test_hash_function);

	my_map.insert(make_pair(54, 'a'));
	my_map.insert(make_pair(54, 'b'));

	REQUIRE(*my_map[54] == 'a');
}
