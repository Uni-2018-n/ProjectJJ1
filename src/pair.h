#ifndef PAIR_H
#define PAIR_H

namespace simple
{

template <class T1, class T2>
struct pair
{
	pair(const T1& first, const T2& second) : m_first(first), m_second(second) {}

	T1 m_first;
	T2 m_second;
};

} // namespace simple

#endif // PAIR_H
