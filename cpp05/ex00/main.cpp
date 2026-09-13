#include <iostream>
#include "Bureaucrat.hpp"

// exercises the constructor bounds and the insertion operator
static void testConstruction()
{
	std::cout << "-- construction --" << std::endl;
	try
	{
		Bureaucrat a("Alice", 1);
		std::cout << a << std::endl;
		Bureaucrat b("Bob", 150);
		std::cout << b << std::endl;
		Bureaucrat tooHigh("TooHigh", 0);
		std::cout << tooHigh << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught: " << e.what() << std::endl;
	}
	try
	{
		Bureaucrat tooLow("TooLow", 151);
		std::cout << tooLow << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught: " << e.what() << std::endl;
	}
}

// exercises increment/decrement and their exceptions at the boundaries
static void testGradeChanges()
{
	std::cout << "-- grade changes --" << std::endl;
	try
	{
		Bureaucrat c("Charlie", 2);
		c.incrementGrade();
		std::cout << c << std::endl;
		c.incrementGrade();
		std::cout << c << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught: " << e.what() << std::endl;
	}
	try
	{
		Bureaucrat d("Dave", 149);
		d.decrementGrade();
		std::cout << d << std::endl;
		d.decrementGrade();
		std::cout << d << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught: " << e.what() << std::endl;
	}
}

int main()
{
	testConstruction();
	testGradeChanges();
	return (0);
}
