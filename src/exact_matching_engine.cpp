#include "exact_matching_engine.h"

#include "vector.h"
#include "string.h"

using bud::string;
using bud::vector;

exact_matching_engine::exact_matching_engine(bud::vector<bud::vector<bud::string*>*>* queries) :
	inverted_search_engine(queries)
{
}

vector<vector<string>> exact_matching_engine::find(string& word, int /*threshold*/) const
{
	vector<vector<string>> return_vector;

	vector<vector<string*>*>* found_ptr = m_hash_map->operator[](&word);
	if (found_ptr != nullptr)
		return_vector = copy_query_vector(*found_ptr);

	return return_vector;
}
