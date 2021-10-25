#include "../lib/include/catch2/catch.hpp"

#include <cstdio>

#include "../src/util.h"
#include "../src/vector.h"
#include "../src/string.h"

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

TEST_CASE("Read empty file and convert contents to vector.", "[empty_file_to_vector]")
{
	FILE* fp = fopen("../queries/query_0.txt", "r");

	REQUIRE(fp != nullptr);

	vector<vector<string*>*>* queries = read_queries_into_vector(fp);

	fclose(fp);

	REQUIRE(queries == nullptr);
}

TEST_CASE("Read file with one item and convert contents to vector.",
		  "[file_with_one_item_to_vector]")
{
	FILE* fp = fopen("../queries/query_1.txt", "r");

	REQUIRE(fp != nullptr);

	vector<vector<string*>*>* queries = read_queries_into_vector(fp);

	fclose(fp);

	REQUIRE(queries->size() == 1);

	REQUIRE(*(queries->operator[](0)->operator[](0)) == string("this"));

	delete_vector_of_vectors_of_strings(queries);
}

TEST_CASE("Read file query with multiple words and convert contents to vector.",
		  "[file_one_query_words_to_vector]")
{
	FILE* fp = fopen("../queries/query_2.txt", "r");

	REQUIRE(fp != nullptr);

	vector<vector<string*>*>* queries = read_queries_into_vector(fp);

	fclose(fp);

	REQUIRE(queries->size() == 2);

	REQUIRE(queries->operator[](0)->size() == 3);
	REQUIRE(*(queries->operator[](0)->operator[](0)) == string("these"));
	REQUIRE(*(queries->operator[](0)->operator[](1)) == string("are"));
	REQUIRE(*(queries->operator[](0)->operator[](2)) == string("some"));

	REQUIRE(queries->operator[](1)->size() == 2);
	REQUIRE(*(queries->operator[](1)->operator[](0)) == string("different"));
	REQUIRE(*(queries->operator[](1)->operator[](1)) == string("words"));

	delete_vector_of_vectors_of_strings(queries);
}

TEST_CASE("Read empty document.", "[read_empty_document]")
{
	FILE* fp = fopen("../documents/document_0.txt", "r");

	REQUIRE(fp != nullptr);

	vector<string> document_words = read_unique_words_into_vector(fp);

	fclose(fp);

	REQUIRE(document_words.size() == 0);
}

TEST_CASE("Read document with no duplicate words.", "[read_document_no_duplicate]")
{
	FILE* fp = fopen("../documents/document_1.txt", "r");

	REQUIRE(fp != nullptr);

	vector<string> document_words = read_unique_words_into_vector(fp);

	fclose(fp);

	REQUIRE(document_words.size() == 3);

	REQUIRE(document_words[0] == bud::string("word"));
	REQUIRE(document_words[1] == bud::string("another"));
	REQUIRE(document_words[2] == bud::string("text"));
}

TEST_CASE("Read document with duplicate words.", "[read_document_duplicate]")
{
	FILE* fp = fopen("../documents/document_2.txt", "r");

	REQUIRE(fp != nullptr);

	vector<string> document_words = read_unique_words_into_vector(fp);

	fclose(fp);

	REQUIRE(document_words.size() == 6);

	REQUIRE(document_words[0] == bud::string("this"));
	REQUIRE(document_words[1] == bud::string("document"));
	REQUIRE(document_words[2] == bud::string("contains"));
	REQUIRE(document_words[3] == bud::string("many"));
	REQUIRE(document_words[4] == bud::string("duplicate"));
	REQUIRE(document_words[5] == bud::string("words"));
}

TEST_CASE("Compare pointers and non pointers.", "[compare_pointers_and_non_pointers]")
{
	int x = 5;
	int y = 5;

	REQUIRE(compare_values(x, y));
	REQUIRE(compare_values(&x, &y));
}
