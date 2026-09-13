#include <iostream>
#include <string>
#include "iter.hpp"

// modifies its argument: needs a non-const reference, so array can't be const
template <typename T>
void doubleValue(T& value)
{
	value = value * 2;
}

// only reads its argument: works with either a const or non-const reference
template <typename T>
void printValue(T const& value)
{
	std::cout << value << " ";
}

int main()
{
	int ints[] = { 1, 2, 3, 4, 5 };
	const std::size_t intsLen = sizeof(ints) / sizeof(ints[0]);

	std::cout << "-- non-const int array --" << std::endl;
	iter(ints, intsLen, printValue<int>);
	std::cout << std::endl;
	iter(ints, intsLen, doubleValue<int>);
	iter(ints, intsLen, printValue<int>);
	std::cout << std::endl;

	const std::string words[] = { "hello", "template", "world" };
	const std::size_t wordsLen = sizeof(words) / sizeof(words[0]);

	std::cout << "-- const string array --" << std::endl;
	iter(words, wordsLen, printValue<std::string>);
	std::cout << std::endl;

	return (0);
}
