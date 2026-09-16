#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

namespace ft_iter_detail
{
	template <typename T> struct IsConst { enum { value = 0 }; };
	template <typename T> struct IsConst<const T> { enum { value = 1 }; };

	template <bool B, typename T = void> struct EnableIf {};
	template <typename T> struct EnableIf<true, T> { typedef T type; };

	template <typename T> struct Identity { typedef T type; };
}

template <typename T>
void iter(T* array, std::size_t length, void (*f)(typename ft_iter_detail::Identity<T>::type const&))
{
	for (std::size_t i = 0; i < length; i++)
		f(array[i]);
}

template <typename T>
typename ft_iter_detail::EnableIf<!ft_iter_detail::IsConst<T>::value>::type
iter(T* array, std::size_t length, void (*f)(typename ft_iter_detail::Identity<T>::type&))
{
	for (std::size_t i = 0; i < length; i++)
		f(array[i]);
}

#endif
