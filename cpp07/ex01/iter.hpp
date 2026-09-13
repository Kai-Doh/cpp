#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

// calls f on every element of array[0..length); works for const or non-const T,
// as long as the functor f accepts what is passed to it
template <typename T, typename F>
void iter(T* array, std::size_t length, F f)
{
	for (std::size_t i = 0; i < length; i++)
		f(array[i]);
}

#endif
