#include "../lib/include/catch2/catch.hpp"

#include "../src/string.h"
#include "../src/bkTrees/bkTree.h"
#include <iostream>
#include <stdexcept>

using bud::string;
using bud::vector;

void delete_vector_of_vectors_of_strings(vector<vector<string*>*>* my_vec);

void delete_vector_of_vectors_of_strings(vector<vector<string*>*>* my_vec)
{
	for (auto* in_vec : *my_vec)
	{
		for (auto* word : *in_vec)
		{
			delete word;
		}

		delete in_vec;
	}

	delete my_vec;
}

TEST_CASE("simple bk test", "[bk_tests1]")
{
	FILE* queries_fp = fopen("../queries/query_5.txt", "r");

	bud::vector<bud::vector<bud::string*>*>* queries = read_queries_into_vector(queries_fp);

	fclose(queries_fp);

	try
	{
		bkTree temp(queries);
		vector<string*> p = temp.find(string("ops"), 2);
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
	delete_vector_of_vectors_of_strings(queries);
}

TEST_CASE("more bk test", "[bk_tests2]")
{
	FILE* queries_fp = fopen("../queries/query_5.txt", "r");

	bud::vector<bud::vector<bud::string*>*>* queries = read_queries_into_vector(queries_fp);

	fclose(queries_fp);

	try
	{
		bkTree temp(queries);
		vector<string*> p = temp.find(string("helt"), 2);
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
	delete_vector_of_vectors_of_strings(queries);
}

TEST_CASE("empty vec bk test", "[bk_tests3]")
{
	FILE* queries_fp = fopen("../queries/query_0.txt", "r");

	bud::vector<bud::vector<bud::string*>*>* queries = read_queries_into_vector(queries_fp);

	fclose(queries_fp);

	try
	{
		bkTree temp(queries);
		vector<string*> p = temp.find(string("helt"), 2);
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
	delete_vector_of_vectors_of_strings(queries);
}
