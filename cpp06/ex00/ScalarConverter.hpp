#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter
{
	public:
		static void convert(const std::string& literal);

	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter& other);
		ScalarConverter& operator=(const ScalarConverter& other);
		~ScalarConverter();

		static bool isCharLiteral(const std::string& literal);
		static bool isIntLiteral(const std::string& literal);
		static bool isFloatLiteral(const std::string& literal);
		static bool isDoubleLiteral(const std::string& literal);

		static void printFromChar(char c);
		static void printFromInt(int i);
		static void printFromFloat(float f);
		static void printFromDouble(double d);

		static void printCharFromValue(double value);
};

#endif
