#ifndef UTIL_H
#define UTIL_H

#include <cstdio>
#include <cstdint>

#include "core.h"

// TODO: Create tests for these function, once you have standard files.
inline int64_t get_number_of_lines(FILE* fp)
{
	fseek(fp, 0L, SEEK_END);
	return ftell(fp);
}

inline int64_t get_approximate_number_of_queries(FILE* fp)
{
	int64_t num_of_lines = get_number_of_lines(fp);
	if (num_of_lines == -1)
		return -1;

	fseek(fp, 0L, SEEK_SET);

	return num_of_lines / (MAX_QUERY_WORDS / 2 + 1);
}

inline int64_t get_approximate_number_of_documents(FILE* fp)
{
	int64_t num_of_lines = get_number_of_lines(fp);
	if (num_of_lines == -1)
		return -1;

	fseek(fp, 0L, SEEK_SET);

	return num_of_lines / (MAX_DOC_LENGTH / 2 + 1);
}

#endif // UTIL_H
