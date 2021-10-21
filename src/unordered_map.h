#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include <cstddef>

#include "forward_list.h"
#include "vector.h"
#include "core.h"
#include "pair.h"

namespace simple
{

using size_type = std::size_t;

template <class Key, class T, class Hash>
class unordered_map
{
public:
	using key_type = Key;
	using mapped_type = T;
	using value_type = pair<const Key, T>;
	using reference = value_type&;
	using const_reference = const value_type&;
	using hasher = Hash;

	explicit unordered_map(size_type size, hasher hash_function = Hash()) :
		m_items((size == 0) ? 1 : size, forward_list<value_type>()), m_hash_function(hash_function)
	{
	}

	T* operator[](const Key& key) const
	{
		size_type index = get_hash(key);

		auto current_item = m_items[index].front();

		while (current_item != nullptr)
		{
			if (current_item->m_value.m_first == key)
				return &(current_item->m_value.m_second);

			current_item = current_item->m_next;
		}

		return nullptr;
	}

	pair<T*, bool> insert(const_reference value)
	{
		size_type index = get_hash(value.m_first);

		auto current_item = m_items[index].front();

		while (current_item != nullptr)
		{
			if (current_item->m_value.m_first == value.m_first)
				return pair<T*, bool>(&(current_item->m_value.m_second), false);

			current_item = current_item->m_next;
		}

		auto return_value = &(m_items[index].push_back(value)->m_value.m_second);

		return pair<T*, bool>(return_value, true);
	}

private:
	size_type get_hash(Key key) const
	{
		return m_hash_function(static_cast<size_type>(key)) % m_items.size();
	}

	vector<forward_list<value_type>> m_items;
	Hash m_hash_function;
};

} // namespace simple

#endif // UNORDERED_MAP_H
