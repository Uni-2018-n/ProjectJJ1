#ifndef ENTRY_H
#define ENTRY_H

#include "word.h"
#include "vector.h"

struct entry
{
	entry(const word& word, int first_query) : m_word(word)
	{
		m_matching_queries.emplace_back(first_query);
	}

	void add_query(int query) { m_matching_queries.emplace_back(query); }

	const word m_word;
	simple::vector<int> m_matching_queries;
};

#endif // ENTRY_H
