#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

// utility class: cannot be instantiated, only offers the static convert() method
class ScalarConverter
{
	public:
		static void convert(const std::string& literal); // detects the literal's type and prints all four conversions

	private:
		ScalarConverter(); // not instantiable
		ScalarConverter(const ScalarConverter& other); // not instantiable
		ScalarConverter& operator=(const ScalarConverter& other); // not instantiable
		~ScalarConverter(); // not instantiable

		static bool isCharLiteral(const std::string& literal); // true for "'x'" style input
		static bool isIntLiteral(const std::string& literal); // true for an optionally signed integer
		static bool isFloatLiteral(const std::string& literal); // true for a float literal or pseudo-literal
		static bool isDoubleLiteral(const std::string& literal); // true for a double literal or pseudo-literal

		static void printFromChar(char c); // prints the char/int/float/double conversions of a char
		static void printFromInt(int i); // prints the char/int/float/double conversions of an int
		static void printFromFloat(float f); // prints the char/int/float/double conversions of a float
		static void printFromDouble(double d); // prints the char/int/float/double conversions of a double

		static void printCharFromValue(double value); // shared "char:" line for an int/float/double source
};

#endif
