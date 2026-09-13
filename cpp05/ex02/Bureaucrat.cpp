#include "Bureaucrat.hpp"
#include "AForm.hpp"

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Bureaucrat grade is too high");
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Bureaucrat grade is too low");
}

// validates that a grade is within the [1, 150] range, throws otherwise
void Bureaucrat::checkGrade(int grade)
{
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
}

Bureaucrat::Bureaucrat() : _name("Anonymous"), _grade(150)
{
}

Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name), _grade(grade)
{
	checkGrade(grade);
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) : _name(other._name), _grade(other._grade)
{
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this != &other)
		_grade = other._grade; // _name is const and cannot be reassigned
	return (*this);
}

Bureaucrat::~Bureaucrat()
{
}

const std::string& Bureaucrat::getName() const
{
	return (_name);
}

int Bureaucrat::getGrade() const
{
	return (_grade);
}

void Bureaucrat::incrementGrade()
{
	if (_grade - 1 < 1)
		throw Bureaucrat::GradeTooHighException();
	_grade--;
}

void Bureaucrat::decrementGrade()
{
	if (_grade + 1 > 150)
		throw Bureaucrat::GradeTooLowException();
	_grade++;
}

// asks the form to sign itself, reports success or the reason for failure
void Bureaucrat::signForm(AForm& form) const
{
	try
	{
		form.beSigned(*this);
		std::cout << _name << " signed " << form.getName() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << _name << " couldn't sign " << form.getName() << " because " << e.what() << std::endl;
	}
}

// asks the form to execute its action, reports success or the reason for failure
void Bureaucrat::executeForm(const AForm& form) const
{
	try
	{
		form.execute(*this);
		std::cout << _name << " executed " << form.getName() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << _name << " couldn't execute " << form.getName() << " because " << e.what() << std::endl;
	}
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b)
{
	os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
	return (os);
}
