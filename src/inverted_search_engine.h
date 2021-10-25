#ifndef INVERTED_SEARCH_ENGINE_H
#define INVERTED_SEARCH_ENGINE_H

#include <cstdio>
#include <exception>
#include <cstdint>

#include "vector.h"
#include "unordered_map.h"
#include "string.h"

enum match_type
{
	EXACT,
	EDIT_DISTANCE,
	HAMMING_DISTANCE
};

class inverted_search_engine
{
public:
	explicit inverted_search_engine(bud::vector<bud::vector<bud::string*>*>* queries) :
		m_queries(queries)
	{
		if (queries->empty())
			throw std::invalid_argument("Queries vector can't by empty.");

		std::size_t num_of_words = count_words_in_queries();

		m_queries->reserve(num_of_words / (MAX_QUERY_WORDS / 2));
		m_words_from_all_queries.reserve(num_of_words);

		m_hash_map = new bud::unordered_map<bud::string*, bud::vector<bud::vector<bud::string*>*>,
											bud::string::HashFunction>(num_of_words);

		add_queries_to_containers();
	}

	virtual ~inverted_search_engine()
	{
		delete m_hash_map;

		for (auto* vec : *m_queries)
		{
			for (auto* word : *vec)
			{
				delete word;
			}

			delete vec;
		}

		delete m_queries;
	}

	static inverted_search_engine*
	search_engine_factory(bud::vector<bud::vector<bud::string*>*>* queries, match_type match_type);

	virtual bud::vector<bud::vector<bud::string>> find(bud::string& word, int threshold) const = 0;
	virtual bud::vector<bud::vector<bud::string>> find(bud::string& word) const;

	static bud::vector<bud::vector<bud::string>>
	copy_query_vector(const bud::vector<bud::vector<bud::string*>*>& vector_to_copy);

protected:
	void add_queries_to_containers();

	std::size_t count_words_in_queries()
	{
		std::size_t sum = 0;

		for (const auto* query : *m_queries)
		{
			sum += query->size();
		}

		return sum;
	}

	bud::vector<bud::vector<bud::string*>*>* m_queries;

	bud::vector<bud::string*> m_words_from_all_queries;

	bud::unordered_map<bud::string*, bud::vector<bud::vector<bud::string*>*>,
					   bud::string::HashFunction>* m_hash_map;
};

#endif // INVERTED_SEARCH_ENGINE_H
