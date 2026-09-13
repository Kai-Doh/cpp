#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <cstddef>

namespace
{
	// one small factory function per concrete form, all sharing the same signature
	AForm* createShrubbery(const std::string& target) { return (new ShrubberyCreationForm(target)); }
	AForm* createRobotomy(const std::string& target) { return (new RobotomyRequestForm(target)); }
	AForm* createPardon(const std::string& target) { return (new PresidentialPardonForm(target)); }

	typedef AForm* (*FormCreator)(const std::string&);

	struct FormEntry
	{
		const char*	name;
		FormCreator	create;
	};
}

Intern::Intern()
{
}

Intern::Intern(const Intern& /* other */)
{
}

Intern& Intern::operator=(const Intern& /* other */)
{
	return (*this);
}

Intern::~Intern()
{
}

// looks up formName in a table instead of an if/else-if ladder, then delegates creation
AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
{
	static const FormEntry forms[] =
	{
		{ "shrubbery creation", &createShrubbery },
		{ "robotomy request", &createRobotomy },
		{ "presidential pardon", &createPardon }
	};
	const std::size_t formCount = sizeof(forms) / sizeof(forms[0]);

	for (std::size_t i = 0; i < formCount; i++)
	{
		if (formName == forms[i].name)
		{
			std::cout << "Intern creates " << formName << std::endl;
			return (forms[i].create(target));
		}
	}
	std::cout << "Intern could not find a form named \"" << formName << "\"" << std::endl;
	return (0);
}
