#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat;

class Form
{
	public:
		// thrown when a required grade would be numerically lower than 1
		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		// thrown when a required grade would be numerically higher than 150
		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		Form(); // default: harmless, already at the lowest requirements
		Form(const std::string& name, int gradeToSign, int gradeToExecute); // validates both grades
		Form(const Form& other); // copy constructor
		Form& operator=(const Form& other); // copies the signed status only, rest is const
		~Form(); // nothing to release

		const std::string&	getName() const; // returns the form's name
		bool				getIsSigned() const; // returns whether the form has been signed
		int					getGradeToSign() const; // returns the grade required to sign
		int					getGradeToExecute() const; // returns the grade required to execute

		void beSigned(const Bureaucrat& bureaucrat); // signs the form if the bureaucrat's grade is high enough

	private:
		const std::string	_name;
		bool				_isSigned;
		const int			_gradeToSign;
		const int			_gradeToExecute;

		static void checkGrade(int grade); // throws if grade is out of [1, 150]
};

std::ostream& operator<<(std::ostream& os, const Form& form); // prints the form's information

#endif
