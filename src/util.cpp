#include "util.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <exception>
#include <utility>

#include "core.h"
#include "vector.h"
#include "string.h"
#include "unordered_map.h"

using bud::string;
using bud::vector;

std::size_t get_approximate_number_of_queries(std::size_t size_of_file)
{
	return size_of_file / (MAX_QUERY_LENGTH / 2 + 1);
}

std::size_t get_approximate_number_of_words(std::size_t size_of_file)
{
	return size_of_file / (MAX_WORD_LENGTH / 2);
}

int64_t get_size_of_file(FILE* fp)
{
	int result = fseek(fp, 0L, SEEK_END);
	if (result == -1)
		throw std::system_error();

	int64_t size = ftell(fp);

	result = fseek(fp, 0L, SEEK_SET);
	if (result == -1)
		throw std::system_error();

	return size;
}

vector<string> read_unique_words_into_vector(FILE* fp)
{
	bud::vector<bud::string> unique_words;

	int64_t size_of_file = get_size_of_file(fp);
	if (size_of_file == 0)
		return unique_words;

	std::size_t apr_num_of_unique_words =
		get_approximate_number_of_words(static_cast<size_t>(size_of_file)) /
		SAME_WORDS_PER_DOCUMENT_FACTOR;

	unique_words.reserve(apr_num_of_unique_words);

	bud::unordered_map<bud::string, bool, HashFunction> hash_map(apr_num_of_unique_words + 1);

	char* buffer = nullptr;

	while (true)
	{
		size_t len = MAX_WORD_LENGTH + 1;

		ssize_t chars_read = getline(&buffer, &len, fp);
		if (chars_read == -1)
			break;

		buffer[chars_read - 1] = '\0';

		bud::string new_word(buffer);

		if (hash_map[new_word] == nullptr)
		{
			unique_words.emplace_back(buffer);
			hash_map.insert(bud::pair<const bud::string, bool>(new_word, true));
		}
	}

	free(buffer);

	return unique_words;
}

vector<vector<string*>> read_queries_into_vector(FILE* fp)
{
	int64_t size_of_file = get_size_of_file(fp);
	if (size_of_file == 0)
		return vector<vector<string*>>();

	std::size_t apr_num_of_queries =
		get_approximate_number_of_queries(static_cast<std::size_t>(size_of_file));

	std::size_t apr_num_of_words_per_query =
		get_approximate_number_of_words(static_cast<std::size_t>(size_of_file)) /
		(apr_num_of_queries + 1);

	vector<vector<string*>> queries_vector;
	queries_vector.reserve(apr_num_of_queries);

	vector<string*> query;
	query.reserve(apr_num_of_words_per_query);

	char* buffer = nullptr;

	while (true)
	{
		size_t len = MAX_WORD_LENGTH + 1;

		ssize_t chars_read = getline(&buffer, &len, fp);
		if (chars_read == -1)
			break;

		if (buffer[0] != '\n')
			buffer[chars_read - 1] = '\0';

		// We found a new query.
		else
		{
			queries_vector.emplace_back(std::move(query));

			query = vector<string*>();
			query.reserve(apr_num_of_words_per_query);

			continue;
		}

		auto* new_string = new string(buffer);
		query.emplace_back(new_string);
	}

	free(buffer);

	queries_vector.emplace_back(query);

	return queries_vector;
}
