#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

template <typename T, typename F>
void iter(T* array, std::size_t length, F f)
{
	for (std::size_t i = 0; i < length; i++)
		f(array[i]);
}

template <typename T, typename F>
void iter(T const* array, std::size_t length, F f)
{
	for (std::size_t i = 0; i < length; i++)
		f(array[i]);
}

#endif
