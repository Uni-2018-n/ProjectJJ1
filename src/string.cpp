#include "string.h"

bud::string::string(const string& other) { strncpy(m_text, other.m_text, MAX_WORD_LENGTH + 1); }

bud::string::string(const char* other) { strncpy(m_text, other, MAX_WORD_LENGTH + 1); }

bud::string& bud::string::operator=(const bud::string& other)
{
	if (this == &other)
		return *this;

	strncpy(m_text, other.m_text, MAX_WORD_LENGTH + 1);
	return *this;
}

bool bud::string::operator==(const bud::string& other) const
{
	return !(strcmp(m_text, other.m_text));
}

bool bud::string::operator!=(const bud::string& other) const { return !(*this == other); }

char& bud::string::operator[](bud::string::size_type index) { return m_text[index]; }

bud::string::size_type bud::string::size() const { return strlen(m_text); }
