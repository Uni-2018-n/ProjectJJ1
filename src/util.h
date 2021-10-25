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

bud::vector<bud::vector<bud::string*>*>* read_queries_into_vector(FILE* fp);

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

#endif // UTIL_H
