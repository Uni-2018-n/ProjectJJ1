#include "../lib/include/catch2/catch.hpp"

#include "../src/string.h"
#include "../src/bkTrees/bkTree.h"
#include "../src/file_reader.h"
#include <iostream>
#include <stdexcept>

using bud::file_reader;
using bud::string;
using bud::vector;


TEST_CASE("simple bk test", "[bk_tests1]")
{
	file_reader query_file_reader("../queries/query_5.txt");

	vector<vector<string*>> queries = query_file_reader.read_queries();
	

	try
	{
		inverted_search_engine* engine =
        inverted_search_engine::search_engine_factory(queries, match_type::EDIT_DISTANCE);
		// vector<string*> p = temp.find(string("ops"), 2);
		bud::string ss("ops");
		vector<int> p = engine->find(ss, 2);
		for (auto x : p)
		// {
		// 	std::cout << x->m_text << std::endl;
		// }
		REQUIRE(p.size() == 2);
	}
	catch (const std::invalid_argument& ia)
	{
		std::cerr << ia.what() << std::endl;
	}
}

TEST_CASE("more bk test", "[bk_tests2]")
{
	file_reader query_file_reader("../queries/query_5.txt");

	vector<vector<string*>> queries = query_file_reader.read_queries();
	
	try
	{
		inverted_search_engine* engine =
        inverted_search_engine::search_engine_factory(queries, match_type::EDIT_DISTANCE);
		bud::string ss("helt");
		vector<int> p = engine->find(ss, 2);
		for (auto x : p)
		// {
		// 	std::cout << x->m_text << std::endl;
		// }
		REQUIRE(p.size() == 6);
	}
	catch (const std::invalid_argument& ia)
	{
		std::cerr << ia.what() << std::endl;
	}
}

TEST_CASE("empty vec bk test", "[bk_tests3]")
{
	file_reader query_file_reader("../queries/query_0.txt");

	vector<vector<string*>> queries = query_file_reader.read_queries();
	
	try
	{
		inverted_search_engine* engine =
        inverted_search_engine::search_engine_factory(queries, match_type::EDIT_DISTANCE);
		bud::string ss("helt");
		vector<int> p = engine->find(ss, 2);
		for (auto x : p)
		// {
		// 	std::cout << x->m_text << std::endl;
		// }
		REQUIRE(p.size() == 6);
	}
	catch (const std::invalid_argument& ia)
	{
		std::cerr << ia.what() << std::endl;
	}
}
