#include <iostream>
#include <string>
#include "iter.hpp"

template <typename T>
void doubleValue(T& value)
{
	value = value * 2;
}

template <typename T>
void printValue(T const& value)
{
	std::cout << value << " ";
}

class Awesome
{
	public:
		Awesome(void) : _n(42) {}
		int get(void) const { return (_n); }
	private:
		int _n;
};

std::ostream& operator<<(std::ostream& o, Awesome const& rhs)
{
	o << rhs.get();
	return (o);
}

template <typename T>
void print(T const& x)
{
	std::cout << x << std::endl;
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

	std::cout << "-- int array and class array --" << std::endl;
	int tab[] = { 0, 1, 2, 3, 4 };
	Awesome tab2[5];
	iter(tab, 5, print<int>);
	iter(tab2, 5, print<Awesome>);

	return (0);
}
