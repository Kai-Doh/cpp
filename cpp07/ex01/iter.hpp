#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

// hand-rolled trait helpers (no <type_traits> in C++98): detect a const-qualified
// type, and SFINAE-disable an overload when a condition doesn't hold
namespace ft_iter_detail
{
	template <typename T> struct IsConst { enum { value = 0 }; };
	template <typename T> struct IsConst<const T> { enum { value = 1 }; };

	template <bool B, typename T = void> struct EnableIf {};
	template <typename T> struct EnableIf<true, T> { typedef T type; };
}

// calls f on every element of array[0..length); f reads each element without modifying it.
// Using a concrete function-pointer type (rather than a free template parameter) lets the
// compiler resolve a plain template function name passed by the caller, e.g. iter(tab, 5, print).
template <typename T>
void iter(T* array, std::size_t length, void (*f)(T const&))
{
	for (std::size_t i = 0; i < length; i++)
		f(array[i]);
}

// same, but for a function that mutates each element in place. Disabled via SFINAE when T is
// already const, otherwise this overload and the one above would collapse to the same signature
// (T& and T const& are identical once T itself is const) and every call would be ambiguous.
template <typename T>
typename ft_iter_detail::EnableIf<!ft_iter_detail::IsConst<T>::value>::type
iter(T* array, std::size_t length, void (*f)(T&))
{
	for (std::size_t i = 0; i < length; i++)
		f(array[i]);
}

#endif
