#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target) :
	AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other) :
	AForm(other), _target(other._target)
{
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

// writes a small ASCII tree into a file named "<target>_shrubbery"
void ShrubberyCreationForm::action() const
{
	std::ofstream file((_target + "_shrubbery").c_str());

	if (!file.is_open())
	{
		std::cout << "ShrubberyCreationForm: could not create file for " << _target << std::endl;
		return ;
	}
	file << "       *\n";
	file << "      ***\n";
	file << "     *****\n";
	file << "    *******\n";
	file << "       |\n";
	file << std::endl;
	file.close();
	std::cout << _target << " has been planted with shrubbery." << std::endl;
}
