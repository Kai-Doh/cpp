#include "AForm.hpp"
#include "Bureaucrat.hpp"

const char* AForm::GradeTooHighException::what() const throw()
{
	return ("Form grade is too high");
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return ("Form grade is too low");
}

const char* AForm::FormNotSignedException::what() const throw()
{
	return ("Form is not signed");
}

// validates that a grade is within the [1, 150] range, throws otherwise
void AForm::checkGrade(int grade)
{
	if (grade < 1)
		throw AForm::GradeTooHighException();
	if (grade > 150)
		throw AForm::GradeTooLowException();
}

AForm::AForm() : _name("Anonymous"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150)
{
}

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute) :
	_name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	checkGrade(gradeToSign);
	checkGrade(gradeToExecute);
}

AForm::AForm(const AForm& other) :
	_name(other._name), _isSigned(other._isSigned),
	_gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
}

AForm& AForm::operator=(const AForm& other)
{
	if (this != &other)
		_isSigned = other._isSigned; // the rest is const and defined at construction
	return (*this);
}

AForm::~AForm()
{
}

const std::string& AForm::getName() const
{
	return (_name);
}

bool AForm::getIsSigned() const
{
	return (_isSigned);
}

int AForm::getGradeToSign() const
{
	return (_gradeToSign);
}

int AForm::getGradeToExecute() const
{
	return (_gradeToExecute);
}

// marks the form as signed, provided the bureaucrat's grade is high enough
void AForm::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > _gradeToSign)
		throw AForm::GradeTooLowException();
	_isSigned = true;
}

// checks the form is signed and the executor's grade is sufficient, then runs the action
void AForm::execute(const Bureaucrat& executor) const
{
	if (!_isSigned)
		throw AForm::FormNotSignedException();
	if (executor.getGrade() > _gradeToExecute)
		throw AForm::GradeTooLowException();
	action();
}

std::ostream& operator<<(std::ostream& os, const AForm& form)
{
	os << form.getName() << ", form requires grade " << form.getGradeToSign()
		<< " to sign and grade " << form.getGradeToExecute() << " to execute. Status: "
		<< (form.getIsSigned() ? "signed" : "not signed") << ".";
	return (os);
}
