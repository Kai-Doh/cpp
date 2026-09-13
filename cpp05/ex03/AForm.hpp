#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat;

// abstract base for every form: holds the shared name/signed/grade state
class AForm
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

		// thrown by execute() when the form has not been signed yet
		class FormNotSignedException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		AForm(); // default: harmless, already at the lowest requirements
		AForm(const std::string& name, int gradeToSign, int gradeToExecute); // validates both grades
		AForm(const AForm& other); // copy constructor
		AForm& operator=(const AForm& other); // copies the signed status only, rest is const
		virtual ~AForm(); // virtual: derived classes are destroyed through this base

		const std::string&	getName() const; // returns the form's name
		bool				getIsSigned() const; // returns whether the form has been signed
		int					getGradeToSign() const; // returns the grade required to sign
		int					getGradeToExecute() const; // returns the grade required to execute

		void beSigned(const Bureaucrat& bureaucrat); // signs the form if the bureaucrat's grade is high enough
		void execute(const Bureaucrat& executor) const; // checks signed + grade, then performs the action

	protected:
		virtual void action() const = 0; // the concrete effect of the form, defined by subclasses

	private:
		const std::string	_name;
		bool				_isSigned;
		const int			_gradeToSign;
		const int			_gradeToExecute;

		static void checkGrade(int grade); // throws if grade is out of [1, 150]
};

std::ostream& operator<<(std::ostream& os, const AForm& form); // prints the form's information

#endif
