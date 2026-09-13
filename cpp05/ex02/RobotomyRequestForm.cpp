#include "RobotomyRequestForm.hpp"
#include <cstdlib>

RobotomyRequestForm::RobotomyRequestForm(const std::string& target) :
	AForm("RobotomyRequestForm", 72, 45), _target(target)
{
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other) :
	AForm(other), _target(other._target)
{
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

// prints drilling noises, then reports success 50% of the time
void RobotomyRequestForm::action() const
{
	std::cout << "* drilling noises *" << std::endl;
	if (std::rand() % 2 == 0)
		std::cout << _target << " has been robotomized successfully." << std::endl;
	else
		std::cout << "The robotomy of " << _target << " failed." << std::endl;
}
