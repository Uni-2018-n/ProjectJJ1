#ifndef WORD_H
#define WORD_H

#include "core.h"
#include <cstring>

struct word
{
	word() = default;
	explicit word(const char* other) { strncpy(m_text, other, MAX_WORD_LENGTH + 1); }

	bool operator==(const word& other) const { return !(strcmp(m_text, other.m_text)); }

	bool operator!=(const word& other) const { return !(*this == other); }

	struct HashFunction
	{
		std::size_t operator()(const word& value) const
		{
			std::size_t i = 0;

			for (int j = 0; value.m_text[j]; j++)
				i += static_cast<std::size_t>(value.m_text[j]);

			return i;
		}
	};

	char m_text[MAX_WORD_LENGTH + 1] = {};
};

#endif // WORD_H
