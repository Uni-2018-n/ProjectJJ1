#ifndef UTIL_H
#define UTIL_H

#include <cstddef>

#include "string.h"

template <typename T>
[[nodiscard]] bool compare_values(const T& first, const T& second)
{
	return first == second;
}

template <typename T>
[[nodiscard]] bool compare_values(T* first, T* second)
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

	std::size_t operator()(const bud::string* value) const
	{
		std::size_t i = 0;

		for (std::size_t j = 0; value->m_text[j]; j++)
			i += static_cast<std::size_t>(value->m_text[j]);

		return i;
	}

	std::size_t operator()(int value) const { return static_cast<size_t>(value); }
};

#endif // UTIL_H
