#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

// signs then executes a form with a bureaucrat, exercising both success and failure paths
static void runForm(AForm& form, Bureaucrat& signer, Bureaucrat& executor)
{
	std::cout << form << std::endl;
	signer.signForm(form);
	executor.executeForm(form);
	std::cout << std::endl;
}

int main()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	Bureaucrat boss("Boss", 1);
	Bureaucrat clerk("Clerk", 140);

	ShrubberyCreationForm shrubbery("garden");
	RobotomyRequestForm robotomy("Bender");
	PresidentialPardonForm pardon("Fry");

	std::cout << "-- executed by the boss (should all succeed) --" << std::endl;
	runForm(shrubbery, boss, boss);
	runForm(robotomy, boss, boss);
	runForm(pardon, boss, boss);

	std::cout << "-- executed by a low-grade clerk (should all fail) --" << std::endl;
	ShrubberyCreationForm shrubbery2("backyard");
	RobotomyRequestForm robotomy2("Bender");
	PresidentialPardonForm pardon2("Leela");
	runForm(shrubbery2, clerk, clerk);
	runForm(robotomy2, clerk, clerk);
	runForm(pardon2, clerk, clerk);

	std::cout << "-- executing an unsigned form --" << std::endl;
	PresidentialPardonForm unsignedForm("Zoidberg");
	boss.executeForm(unsignedForm);

	return (0);
}
