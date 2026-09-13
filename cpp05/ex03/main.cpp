#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Intern.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"

int main()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	Intern someRandomIntern;
	Bureaucrat boss("Boss", 1);

	std::cout << "-- creating every known form --" << std::endl;
	const std::string names[3] = { "shrubbery creation", "robotomy request", "presidential pardon" };
	for (int i = 0; i < 3; i++)
	{
		AForm* form = someRandomIntern.makeForm(names[i], "Bender");
		if (form)
		{
			boss.signForm(*form);
			boss.executeForm(*form);
			delete form;
		}
		std::cout << std::endl;
	}

	std::cout << "-- unknown form name --" << std::endl;
	AForm* unknown = someRandomIntern.makeForm("form 28B", "nobody");
	delete unknown;

	return (0);
}
