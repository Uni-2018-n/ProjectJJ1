#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <cstddef>

#include "core.h"

namespace bud
{

struct string
{
	using size_type = std::size_t;

	string() = default;

	string(const string& other);

	explicit string(const char* other);

	constexpr string& operator=(const bud::string& other);

	bool operator==(const string& other) const;

	bool operator!=(const string& other) const;

	char& operator[](size_type index);

	size_type size();

	struct HashFunction
	{
		size_type operator()(const bud::string& value) const
		{
			size_type i = 0;

			for (size_type j = 0; value.m_text[j]; j++)
				i += static_cast<std::size_t>(value.m_text[j]);

			return i;
		}

		size_type operator()(bud::string* value) const
		{
			size_type i = 0;

			for (size_type j = 0; value->m_text[j]; j++)
				i += static_cast<std::size_t>(value->m_text[j]);

			return i;
		}
	};

	char m_text[MAX_WORD_LENGTH + 1] = {};
};

} // namespace bud

#endif // STRING_H
