#ifndef WORD_H
#define WORD_H

#include <cstring>

#include "core.h"

namespace simple
{

struct string
{
	using size_type = std::size_t;

	string() = default;

	string(const string& other) { strncpy(m_text, other.m_text, MAX_WORD_LENGTH + 1); }

	explicit string(const char* other) { strncpy(m_text, other, MAX_WORD_LENGTH + 1); }

	constexpr string& operator=(const char* other)
	{
		strncpy(m_text, other, MAX_WORD_LENGTH + 1);
		return *this;
	}

	bool operator==(const string& other) const { return !(strcmp(m_text, other.m_text)); }

	bool operator!=(const string& other) const { return !(*this == other); }

	char& operator[](size_type index) { return m_text[index]; }

	struct HashFunction
	{
		std::size_t operator()(const string& value) const
		{
			size_type i = 0;

			for (size_type j = 0; value.m_text[j]; j++)
				i += static_cast<std::size_t>(value.m_text[j]);

			return i;
		}
	};

	char m_text[MAX_WORD_LENGTH + 1] = {};
};

} // namespace simple

#endif // WORD_H
