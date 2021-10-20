#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <cstddef>

namespace simple
{

template <class T>
struct forward_list_node
{
	explicit forward_list_node(const T& value) : m_value(value) {}

	forward_list_node* m_next = nullptr;
	T m_value;
};

template <class T>
class forward_list
{
	using value_type = T;
	using pointer_type = T*;
	using reference = value_type&;
	using const_reference = const value_type&;
	using node = forward_list_node<T>;
	using node_pointer = node*;

public:
	forward_list() = default;

	~forward_list()
	{
		while (m_head != nullptr)
		{
			node_pointer next_node = m_head->m_next;
			delete m_head;
			m_head = next_node;
		}
	}

	void push_back(const_reference item)
	{
		auto new_node = new node(item);

		if (m_head == nullptr)
		{
			m_head = new_node;
			m_tail = new_node;
		}

		else
		{
			m_tail->m_next = new_node;
			m_tail = m_tail->m_next;
		}
	}

	bool empty() { return m_head == nullptr; }

	node_pointer front() { return m_head; }

private:
	node_pointer m_head = nullptr;
	node_pointer m_tail = nullptr;
};

} // namespace simple

#endif // FORWARD_LIST_H
