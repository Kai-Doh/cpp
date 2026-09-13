#include "Form.hpp"
#include "Bureaucrat.hpp"

const char* Form::GradeTooHighException::what() const throw()
{
	return ("Form grade is too high");
}

const char* Form::GradeTooLowException::what() const throw()
{
	return ("Form grade is too low");
}

// validates that a grade is within the [1, 150] range, throws otherwise
void Form::checkGrade(int grade)
{
	if (grade < 1)
		throw Form::GradeTooHighException();
	if (grade > 150)
		throw Form::GradeTooLowException();
}

Form::Form() : _name("Anonymous"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150)
{
}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute) :
	_name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	checkGrade(gradeToSign);
	checkGrade(gradeToExecute);
}

Form::Form(const Form& other) :
	_name(other._name), _isSigned(other._isSigned),
	_gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
}

Form& Form::operator=(const Form& other)
{
	if (this != &other)
		_isSigned = other._isSigned; // the rest is const and defined at construction
	return (*this);
}

Form::~Form()
{
}

const std::string& Form::getName() const
{
	return (_name);
}

bool Form::getIsSigned() const
{
	return (_isSigned);
}

int Form::getGradeToSign() const
{
	return (_gradeToSign);
}

int Form::getGradeToExecute() const
{
	return (_gradeToExecute);
}

// marks the form as signed, provided the bureaucrat's grade is high enough
void Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > _gradeToSign)
		throw Form::GradeTooLowException();
	_isSigned = true;
}

std::ostream& operator<<(std::ostream& os, const Form& form)
{
	os << form.getName() << ", form requires grade " << form.getGradeToSign()
		<< " to sign and grade " << form.getGradeToExecute() << " to execute. Status: "
		<< (form.getIsSigned() ? "signed" : "not signed") << ".";
	return (os);
}
