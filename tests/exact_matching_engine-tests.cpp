#include "../lib/include/catch2/catch.hpp"

#include "../src/exact_matching_engine.h"
#include "../src/vector.h"
#include "../src/string.h"
#include "../src/file_reader.h"

using bud::file_reader;
using bud::string;
using bud::vector;

TEST_CASE("Test word not in any query.", "[word_not_in_any_query]")
{
	file_reader query_file_reader("../queries/query_3.txt");

	vector<vector<string*>> queries = query_file_reader.read_queries();

	inverted_search_engine* engine =
		inverted_search_engine::search_engine_factory(queries, match_type::EXACT);

	file_reader document_file_reader("../documents/document_3.txt");

	vector<string> document_words = document_file_reader.read_unique_words();

	vector<int> found_queries = engine->find(document_words[0]);

	REQUIRE(found_queries.empty());

	delete engine;
}

TEST_CASE("Test words in queries.", "[words_in_queries]")
{
	file_reader query_file_reader("../queries/query_4.txt");

	vector<vector<string*>> queries = query_file_reader.read_queries();

	inverted_search_engine* engine =
		inverted_search_engine::search_engine_factory(queries, match_type::EXACT);

	file_reader document_file_reader("../documents/document_4.txt");

	vector<string> document_words = document_file_reader.read_unique_words();

	vector<int> found_queries = engine->find(document_words[0]);
	REQUIRE(found_queries.size() == 2);
	REQUIRE(found_queries[0] == 0);
	REQUIRE(found_queries[1] == 4);

	found_queries = engine->find(document_words[1]);
	REQUIRE(found_queries.size() == 2);
	REQUIRE(found_queries[0] == 1);
	REQUIRE(found_queries[1] == 4);

	found_queries = engine->find(document_words[2]);
	REQUIRE(found_queries.size() == 2);
	REQUIRE(found_queries[0] == 2);
	REQUIRE(found_queries[1] == 4);

	found_queries = engine->find(document_words[3]);
	REQUIRE(found_queries.empty());

	delete engine;
}
