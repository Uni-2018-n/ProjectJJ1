#include "bkTree.h"
#include "../string.h"
#include "../vector.h"
#include "../inverted_search_engine.h"
#include "../unordered_map.h"
#include "../pair.h"

#include "appMatching/editDistance.h"
#include <iostream>
#include <stdexcept>

using bud::pair;
using bud::string;
using bud::unordered_map;
using bud::vector;

bkNode::bkNode(string* s, match_type m)
{
	str = s;
	type = m;
}

void bkNode::add(string* s)
{
	unsigned long curr;
	if (type == EDIT_DISTANCE)
	{
		curr = getEdit(*str, *s);
	}
	else
	{
		curr = 0;
	}
	if (childs[curr] == nullptr)
	{
		childs[curr] = new bkNode(s, type);
	}
	else
	{
		childs[curr]->add(s);
	}
}
bkNode::~bkNode()
{
	for (auto* x : childs)
	{
		delete x;
	}
}

bud::vector<bud::string*> bkNode::find(const bud::string& s, int tol)
{
	vector<string*> fin;
	if (*str != string(""))
	{
		int temp;
		if (type == EDIT_DISTANCE)
		{
			temp = getEdit(*str, s);
		}
		else
		{
			temp = -1;
		}

		if (temp <= tol)
		{
			fin.emplace_back(str);
		}
		for (unsigned long i = temp - tol < 0 ? 1 : unsigned(temp - tol); i <= unsigned(temp + tol);
			 i++)
		{
			if (childs[i] != nullptr)
			{
				vector<string*> t = childs[i]->find(s, tol);
				fin.insert(t.begin(), t.end());
			}
		}
	}
	return fin;
}

bkTree::bkTree(bud::vector<bud::vector<bud::string*>*>* queries, match_type m) // TODO
	:
	inverted_search_engine(queries)
{
	type = m;
	if (m_words_from_all_queries.size() == 0)
	{
		throw std::invalid_argument("Vector is empty!");
		return;
	}
	root = new bkNode(m_words_from_all_queries[0], type);
	for (unsigned i = 1; i < m_words_from_all_queries.size(); i++)
	{
		this->add(m_words_from_all_queries[i]);
	}
}

bkTree::~bkTree() { delete root; }

void bkTree::add(string* s) { root->add(s); }

bud::vector<bud::string*> bkTree::findd(const bud::string& s, int tol) const
{
	return root->find(s, tol);
}

bud::vector<bud::vector<bud::string>> bkTree::find(bud::string& word, int tol) const
{
	bud::vector<bud::string*> words_found = findd(word, tol);

	bud::vector<bud::vector<bud::string*>*> vector_with_pointers;

	bud::unordered_map<vector<string*>*, bool, HashFunction> inserted_queries(m_hash_map->size());

	for (auto* query_word : words_found)
	{
		auto* queries_with_that_word = m_hash_map->operator[](query_word);

		for (auto* query : *queries_with_that_word)
		{
			if (inserted_queries[query] == nullptr)
				vector_with_pointers.emplace_back(query);

			else
				inserted_queries.insert(pair<vector<string*>* const, bool>(query, true));
		}

		vector_with_pointers.insert(queries_with_that_word->begin(), queries_with_that_word->end());
	}

	return copy_query_vector(vector_with_pointers);
}
