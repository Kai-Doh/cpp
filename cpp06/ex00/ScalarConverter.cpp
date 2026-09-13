#include "ScalarConverter.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <limits>

namespace
{
	// formats a floating value the way the exercise expects: "42.0f", "nanf", "+inff", ...
	std::string formatFloating(double value, bool isFloat)
	{
		std::ostringstream oss;

		if (std::isnan(value))
			return (isFloat ? "nanf" : "nan");
		if (std::isinf(value))
			return (std::string(value < 0 ? "-inf" : "+inf") + (isFloat ? "f" : ""));
		oss << value;
		std::string s = oss.str();
		if (s.find('.') == std::string::npos && s.find('e') == std::string::npos)
			s += ".0";
		if (isFloat)
			s += "f";
		return (s);
	}

	// true when the whole string is a signed run of digits, with an optional single '.' if requireDot allows it
	bool isDecimalNumber(const std::string& s, bool requireDot)
	{
		if (s.empty())
			return (false);
		std::size_t i = (s[0] == '+' || s[0] == '-') ? 1 : 0;
		bool sawDigit = false;
		bool sawDot = false;

		for (; i < s.size(); i++)
		{
			if (std::isdigit(static_cast<unsigned char>(s[i])))
				sawDigit = true;
			else if (s[i] == '.' && !sawDot)
				sawDot = true;
			else
				return (false);
		}
		if (!sawDigit)
			return (false);
		if (requireDot != sawDot)
			return (false);
		return (true);
	}
}

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& /* other */) {}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& /* other */) { return (*this); }
ScalarConverter::~ScalarConverter() {}

bool ScalarConverter::isCharLiteral(const std::string& literal)
{
	return (literal.size() == 3 && literal[0] == '\'' && literal[2] == '\'');
}

bool ScalarConverter::isIntLiteral(const std::string& literal)
{
	return (isDecimalNumber(literal, false));
}

bool ScalarConverter::isFloatLiteral(const std::string& literal)
{
	if (literal == "+inff" || literal == "-inff" || literal == "nanf")
		return (true);
	if (literal.empty() || literal[literal.size() - 1] != 'f')
		return (false);
	return (isDecimalNumber(literal.substr(0, literal.size() - 1), true));
}

bool ScalarConverter::isDoubleLiteral(const std::string& literal)
{
	if (literal == "+inf" || literal == "-inf" || literal == "nan")
		return (true);
	return (isDecimalNumber(literal, true));
}

// shared logic for the "char:" line whenever the source is int/float/double
void ScalarConverter::printCharFromValue(double value)
{
	if (std::isnan(value) || std::isinf(value)
		|| value < static_cast<double>(std::numeric_limits<char>::min())
		|| value > static_cast<double>(std::numeric_limits<char>::max()))
	{
		std::cout << "char: impossible" << std::endl;
		return ;
	}
	char c = static_cast<char>(value);
	if (std::isprint(static_cast<unsigned char>(c)))
		std::cout << "char: '" << c << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
}

void ScalarConverter::printFromChar(char c)
{
	if (std::isprint(static_cast<unsigned char>(c)))
		std::cout << "char: '" << c << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << formatFloating(static_cast<double>(static_cast<float>(c)), true) << std::endl;
	std::cout << "double: " << formatFloating(static_cast<double>(c), false) << std::endl;
}

void ScalarConverter::printFromInt(int i)
{
	printCharFromValue(static_cast<double>(i));
	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << formatFloating(static_cast<double>(static_cast<float>(i)), true) << std::endl;
	std::cout << "double: " << formatFloating(static_cast<double>(i), false) << std::endl;
}

void ScalarConverter::printFromFloat(float f)
{
	double d = static_cast<double>(f);

	printCharFromValue(d);
	if (std::isnan(d) || std::isinf(d)
		|| d < static_cast<double>(std::numeric_limits<int>::min())
		|| d > static_cast<double>(std::numeric_limits<int>::max()))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(f) << std::endl;
	std::cout << "float: " << formatFloating(d, true) << std::endl;
	std::cout << "double: " << formatFloating(d, false) << std::endl;
}

void ScalarConverter::printFromDouble(double d)
{
	printCharFromValue(d);
	if (std::isnan(d) || std::isinf(d)
		|| d < static_cast<double>(std::numeric_limits<int>::min())
		|| d > static_cast<double>(std::numeric_limits<int>::max()))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(d) << std::endl;
	std::cout << "float: " << formatFloating(static_cast<double>(static_cast<float>(d)), true) << std::endl;
	std::cout << "double: " << formatFloating(d, false) << std::endl;
}

// detects the literal's real type, then prints its value converted to all four scalar types
void ScalarConverter::convert(const std::string& literal)
{
	if (isCharLiteral(literal))
	{
		printFromChar(literal[1]);
		return ;
	}
	if (isIntLiteral(literal))
	{
		char* end = 0;
		// parsed as a double first: on some platforms "long" is only 32 bits,
		// which would make strtol's own overflow clamping silently hide the overflow
		double value = std::strtod(literal.c_str(), &end);

		if (*end != '\0' || value < static_cast<double>(std::numeric_limits<int>::min())
			|| value > static_cast<double>(std::numeric_limits<int>::max()))
		{
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
			return ;
		}
		printFromInt(static_cast<int>(value));
		return ;
	}
	if (isFloatLiteral(literal))
	{
		float value;

		if (literal == "+inff")
			value = std::numeric_limits<float>::infinity();
		else if (literal == "-inff")
			value = -std::numeric_limits<float>::infinity();
		else if (literal == "nanf")
			value = std::numeric_limits<float>::quiet_NaN();
		else
			value = static_cast<float>(std::strtod(literal.c_str(), 0));
		printFromFloat(value);
		return ;
	}
	if (isDoubleLiteral(literal))
	{
		double value;

		if (literal == "+inf")
			value = std::numeric_limits<double>::infinity();
		else if (literal == "-inf")
			value = -std::numeric_limits<double>::infinity();
		else if (literal == "nan")
			value = std::numeric_limits<double>::quiet_NaN();
		else
			value = std::strtod(literal.c_str(), 0);
		printFromDouble(value);
		return ;
	}
	std::cout << "Invalid literal: could not detect its type" << std::endl;
}
