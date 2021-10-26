#include "../lib/include/catch2/catch.hpp"

#include <cstdio>

#include "../src/exact_matching_engine.h"
#include "../src/util.h"
#include "../src/vector.h"
#include "../src/string.h"

using bud::string;
using bud::vector;

TEST_CASE("Test word not in any query.", "[word_not_in_any_query]")
{
	FILE* queries_fp = fopen("queries/query_3.txt", "r");

	vector<vector<string*>> queries = read_queries_into_vector(queries_fp);

	fclose(queries_fp);

	inverted_search_engine* engine =
		inverted_search_engine::search_engine_factory(queries, match_type::EXACT);

	FILE* documents_fp = fopen("documents/document_3.txt", "r");

	vector<string> document_words = read_unique_words_into_vector(documents_fp);

	fclose(documents_fp);

	vector<int> found_queries = engine->find(document_words[0]);

	REQUIRE(found_queries.empty());

	delete engine;
}

TEST_CASE("Test words in queries.", "[words_in_queries]")
{
	FILE* queries_fp = fopen("queries/query_4.txt", "r");

	vector<vector<string*>> queries = read_queries_into_vector(queries_fp);

	fclose(queries_fp);

	inverted_search_engine* engine =
		inverted_search_engine::search_engine_factory(queries, match_type::EXACT);

	FILE* documents_fp = fopen("documents/document_4.txt", "r");

	vector<string> document_words = read_unique_words_into_vector(documents_fp);

	fclose(documents_fp);

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
