#ifndef WHATEVER_HPP
#define WHATEVER_HPP

// exchanges the values held by a and b
template <typename T>
void swap(T& a, T& b)
{
	T tmp = a;

	a = b;
	b = tmp;
}

// returns the smaller of the two values, or b if they are equal
template <typename T>
T const& min(T const& a, T const& b)
{
	return (a < b ? a : b);
}

// returns the greater of the two values, or b if they are equal
template <typename T>
T const& max(T const& a, T const& b)
{
	return (a > b ? a : b);
}

#endif
