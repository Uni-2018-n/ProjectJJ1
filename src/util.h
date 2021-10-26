#ifndef UTIL_H
#define UTIL_H

#include <cstddef>
#include <cstdio>

#include "core.h"
#include "vector.h"
#include "string.h"

const std::size_t SAME_WORDS_PER_DOCUMENT_FACTOR = 15;

int64_t get_size_of_file(FILE* fp);

std::size_t get_approximate_number_of_queries(std::size_t size_of_file);

std::size_t get_approximate_number_of_words(std::size_t size_of_file);

bud::vector<bud::string> read_unique_words_into_vector(FILE* fp);

bud::vector<bud::vector<bud::string*>> read_queries_into_vector(FILE* fp);

template <typename T>
bool compare_values(const T& first, const T& second)
{
	return first == second;
}

template <typename T>
bool compare_values(T* first, T* second)
{
	return *first == *second;
}

struct HashFunction
{
	std::size_t operator()(const bud::string& value) const
	{
		std::size_t i = 0;

		for (std::size_t j = 0; value.m_text[j]; j++)
			i += static_cast<std::size_t>(value.m_text[j]);

		return i;
	}

	std::size_t operator()(bud::string* value) const
	{
		std::size_t i = 0;

		for (std::size_t j = 0; value->m_text[j]; j++)
			i += static_cast<std::size_t>(value->m_text[j]);

		return i;
	}

	std::size_t operator()(int value) const { return static_cast<size_t>(value); }
};

#endif // UTIL_H
