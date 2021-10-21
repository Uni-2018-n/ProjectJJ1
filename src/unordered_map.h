#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include <cstddef>

#include "forward_list.h"
#include "vector.h"
#include "core.h"

namespace simple
{

using size_type = std::size_t;

template <class Key, class T>
struct unordered_map_item
{
	unordered_map_item(const Key& key, const T& value) : m_key(key), m_value(value) {}

	Key m_key;
	T m_value;
};

template <class Key, class T>
unordered_map_item<Key, T> make_pair(Key key, T value)
{
	return unordered_map_item<Key, T>(key, value);
}

template <class Key, class T, class Hash>
class unordered_map
{
public:
	using key_type = Key;
	using mapped_type = T;
	using value_type = unordered_map_item<Key, T>;
	using reference = value_type&;
	using const_reference = const value_type&;
	using hasher = Hash;

	explicit unordered_map(size_type size, hasher hash_function = Hash()) :
		m_items((size == 0) ? 1 : size, forward_list<unordered_map_item<Key, T>>()),
		m_hash_function(hash_function)
	{
	}

	T* operator[](const Key& key) const
	{
		size_type index = get_hash(key);

		auto current_item = m_items[index].front();

		while (current_item != nullptr)
		{
			if (current_item->m_value.m_key == key)
				return &(current_item->m_value.m_value);

			current_item = current_item->m_next;
		}

		return nullptr;
	}

	T* insert(const_reference value)
	{
		size_type index = get_hash(value.m_key);

		auto current_item = m_items[index].front();

		while (current_item != nullptr)
		{
			if (current_item->m_value.m_key == value.m_key)
				return &(current_item->m_value.m_value);

			current_item = current_item->m_next;
		}

		m_items[index].push_back(value);

		return nullptr;
	}

private:
	size_type get_hash(Key key) const
	{
		return m_hash_function(static_cast<size_type>(key)) % m_items.size();
	}

	vector<forward_list<unordered_map_item<Key, T>>> m_items;
	Hash m_hash_function;
};

} // namespace simple

#endif // UNORDERED_MAP_H
