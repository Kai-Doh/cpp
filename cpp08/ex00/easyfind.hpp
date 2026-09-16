#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>
# include <stdexcept>

// returns an iterator to the first occurrence of value in container, or throws if absent
template <typename T>
typename T::iterator easyfind(T &container, int value)
{
    typename T::iterator it = std::find(container.begin(), container.end(), value);

    if (it == container.end())
        throw std::runtime_error("easyfind: value not found");
    return (it);
}

#endif
