#include "inverted_search_engine.h"

#include "bkTrees/bkTree.h"
#include "string.h"
#include "vector.h"
#include "exact_matching_engine.h"
#include "unordered_map.h"

using bud::pair;
using bud::string;
using bud::vector;

bud::vector<bud::vector<bud::string>> inverted_search_engine::find(bud::string& word) const
{
	return find(word, 0);
}

void inverted_search_engine::add_queries_to_containers()
{
	for (auto* query : *m_queries)
	{
		for (auto* word : *query)
		{
			bud::vector<bud::vector<bud::string*>*>* result = (*m_hash_map)[word];

			if (result == nullptr)
			{
				vector<vector<string*>*> new_vector;
				new_vector.emplace_back(query);

				m_words_from_all_queries.emplace_back(word);
				m_hash_map->insert(
					pair<string* const, vector<vector<string*>*>>(word, std::move(new_vector)));
			}

			else
				result->emplace_back(query);
		}
	}
}

bud::vector<bud::vector<bud::string>> inverted_search_engine::copy_query_vector(
	const bud::vector<bud::vector<bud::string*>*>& vector_to_copy)
{
	vector<vector<string>> return_vector(vector_to_copy.size());

	for (std::size_t i = 0; i < vector_to_copy.size(); i++)
	{
		return_vector[i].reserve(vector_to_copy[i]->size());

		for (std::size_t j = 0; j < vector_to_copy[i]->size(); j++)
		{
			return_vector[i].emplace_back(*vector_to_copy[i]->operator[](j));
		}
	}

	return return_vector;
}

inverted_search_engine*
inverted_search_engine::search_engine_factory(bud::vector<bud::vector<bud::string*>*>* queries,
											  match_type type)
{
	switch (type)
	{
	case EXACT:
		return new exact_matching_engine(queries);
		break;
	default:
		return new bkTree(queries, type);
		break;
	}
}
