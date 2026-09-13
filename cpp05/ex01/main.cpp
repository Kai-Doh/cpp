#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

// exercises Form construction bounds and its insertion operator
static void testFormConstruction()
{
	std::cout << "-- form construction --" << std::endl;
	try
	{
		Form f("Tax Form", 50, 100);
		std::cout << f << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught: " << e.what() << std::endl;
	}
	try
	{
		Form bad("Bad Form", 0, 100);
		std::cout << bad << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught: " << e.what() << std::endl;
	}
}

// exercises signing a form both successfully and unsuccessfully
static void testSigning()
{
	std::cout << "-- signing --" << std::endl;
	Form form("Vacation Request", 50, 100);
	Bureaucrat highGrade("Alice", 10);
	Bureaucrat lowGrade("Bob", 100);

	highGrade.signForm(form);
	std::cout << form << std::endl;

	Form form2("Budget Form", 50, 100);
	lowGrade.signForm(form2);
	std::cout << form2 << std::endl;
}

int main()
{
	testFormConstruction();
	testSigning();
	return (0);
}
