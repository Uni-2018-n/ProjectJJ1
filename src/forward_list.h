#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <cstddef>
#include <iterator>
#include <utility>

namespace bud
{

using size_type = std::size_t;

template <class T>
struct forward_list_node
{
	template <typename... Args>
	explicit forward_list_node(forward_list_node* next, Args&&... value) :
		m_next(next), m_value(std::forward<Args>(value)...)
	{
	}

	forward_list_node* m_next;
	T m_value;
};

template <typename T>
class forward_list_iterator
{
public:
	using value_type = T;
	using pointer = value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::ptrdiff_t;

	using node = forward_list_node<T>;
	using node_pointer = node*;

	forward_list_iterator() = default;

	explicit forward_list_iterator(node_pointer ptr) : m_ptr(ptr) {}

	forward_list_iterator& operator++()
	{
		if (m_ptr != nullptr)
			m_ptr = m_ptr->m_next;

		return *this;
	}

	forward_list_iterator operator++(int)
	{
		forward_list_iterator it(*this);
		if (m_ptr != nullptr)
			m_ptr = m_ptr->m_next;
		return it;
	}

	reference operator*() { return m_ptr->m_value; }

	const_reference operator*() const { return m_ptr->m_value; }

	bool operator==(const forward_list_iterator& other) const { return m_ptr == other.m_ptr; }

	bool operator!=(const forward_list_iterator& other) const { return m_ptr != other.m_ptr; }

private:
	node_pointer m_ptr = nullptr;
};

template <class T>
class forward_list
{
	using value_type = T;
	using reference = value_type&;
	using const_reference = const value_type&;
	using node = forward_list_node<T>;
	using node_pointer = node*;
	using iterator = forward_list_iterator<T>;

public:
	forward_list() = default;

	forward_list(forward_list&& other) noexcept : m_head(other.m_head) { other.m_head = nullptr; }

	~forward_list() { clear(); }

	forward_list& operator=(forward_list&& other) noexcept
	{
		m_head = other.m_head;
		other.m_head = nullptr;

		return *this;
	}

	void clear() noexcept
	{
		while (m_head != nullptr)
		{
			node_pointer temp = m_head->m_next;
			delete m_head;
			m_head = temp;
		}
	}

	void push_front(const_reference item) { emplace_front(item); }

	void push_front(T&& item) { emplace_front(std::move(item)); }

	template <typename... Args>
	reference emplace_front(Args&&... args)
	{
		m_head = new node(m_head, std::forward<Args>(args)...);

		return m_head->m_value;
	}

	bool empty() const noexcept { return m_head == nullptr; }

	reference front() { return m_head->m_value; }

	const_reference front() const { return m_head->m_value; }

	iterator begin() noexcept { return iterator(m_head); }

	iterator begin() const noexcept { return iterator(m_head); }

	iterator cbegin() const noexcept { return iterator(m_head); }

	iterator end() noexcept { return iterator(); }

	iterator end() const noexcept { return iterator(); }

	iterator cend() const noexcept { return iterator(); }

private:
	node_pointer m_head = nullptr;
};

} // namespace bud

#endif // FORWARD_LIST_H
