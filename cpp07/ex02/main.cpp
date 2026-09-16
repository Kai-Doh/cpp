#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Array.hpp"

#define MAX_VAL 750

// a small non-scalar type: owns nothing itself, but forces Array to actually run
// a real constructor/destructor/copy-assignment, unlike a plain int
class Fraction
{
	public:
		Fraction() : _num(0), _den(1) {}
		Fraction(int num, int den) : _num(num), _den(den) {}

		int getNum() const { return (_num); }
		int getDen() const { return (_den); }

	private:
		int _num;
		int _den;
};

std::ostream& operator<<(std::ostream& os, const Fraction& f)
{
	os << f.getNum() << "/" << f.getDen();
	return (os);
}

// proves Array<T> works with non-scalar types too: a class (Fraction, which has
// its own constructor) and std::string (which owns a heap-allocated buffer, so a
// shallow copy of Array would show up here as corruption or a double free)
static void testComplexTypes()
{
	std::cout << "-- Array<std::string> --" << std::endl;
	Array<std::string> words(3);
	words[0] = "hello";
	words[1] = "template";
	words[2] = "world";
	for (unsigned int i = 0; i < words.size(); i++)
		std::cout << words[i] << " ";
	std::cout << std::endl;

	Array<std::string> wordsCopy(words);
	wordsCopy[0] = "changed";
	std::cout << "original[0] after modifying the copy: " << words[0] << std::endl;

	std::cout << "-- Array<Fraction> --" << std::endl;
	Array<Fraction> fractions(2);
	fractions[0] = Fraction(1, 2);
	fractions[1] = Fraction(3, 4);
	std::cout << fractions[0] << " " << fractions[1] << std::endl;

	Array<Fraction> emptyFractions;
	std::cout << "emptyFractions.size() = " << emptyFractions.size() << std::endl;

	try
	{
		fractions[5];
		std::cout << "no throw (unexpected)" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "out-of-range on Array<Fraction>: " << e.what() << std::endl;
	}

	const Array<std::string> constWords(words);
	std::cout << "const access: " << constWords[1] << std::endl;
}

int main(int, char**)
{
	testComplexTypes();
	std::cout << "-- Array<int> --" << std::endl;

	Array<int> numbers(MAX_VAL);
	int* mirror = new int[MAX_VAL];
	srand(time(NULL));
	for (int i = 0; i < MAX_VAL; i++)
	{
		const int value = rand();
		numbers[i] = value;
		mirror[i] = value;
	}
	// SCOPE: copies must not affect the original once they go out of scope
	{
		Array<int> tmp = numbers;
		Array<int> test(tmp);
	}

	for (int i = 0; i < MAX_VAL; i++)
	{
		if (mirror[i] != numbers[i])
		{
			std::cerr << "didn't save the same value!!" << std::endl;
			return 1;
		}
	}
	try
	{
		numbers[-2] = 0;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		numbers[MAX_VAL] = 0;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	for (int i = 0; i < MAX_VAL; i++)
	{
		numbers[i] = rand();
	}

	Array<int> empty;
	std::cout << "empty.size() = " << empty.size() << std::endl;
	std::cout << "numbers.size() = " << numbers.size() << std::endl;
	std::cout << "all checks passed" << std::endl;

	delete [] mirror;
	return 0;
}
