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

	string& operator=(const bud::string& other);

	bool operator==(const string& other) const;

	bool operator!=(const string& other) const;

	char& operator[](size_type index);

	size_type size();

	char m_text[MAX_WORD_LENGTH + 1] = {};
};

} // namespace bud

#endif // STRING_H
