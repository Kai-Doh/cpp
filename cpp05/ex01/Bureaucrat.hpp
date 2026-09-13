#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <exception>

class Form;

class Bureaucrat
{
	public:
		// thrown when a grade would be numerically lower than 1 (i.e. too high in rank)
		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		// thrown when a grade would be numerically higher than 150 (i.e. too low in rank)
		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		Bureaucrat(); // default: lowest valid grade
		Bureaucrat(const std::string& name, int grade); // builds a named bureaucrat, validates grade
		Bureaucrat(const Bureaucrat& other); // copy constructor
		Bureaucrat& operator=(const Bureaucrat& other); // copies the grade only, name is const
		~Bureaucrat(); // nothing to release

		const std::string& getName() const; // returns the bureaucrat's name
		int getGrade() const; // returns the bureaucrat's grade

		void incrementGrade(); // improves the grade (numeric value decreases)
		void decrementGrade(); // worsens the grade (numeric value increases)

		void signForm(Form& form) const; // attempts to sign a form, prints outcome

	private:
		const std::string	_name;
		int					_grade;

		static void checkGrade(int grade); // throws if grade is out of [1, 150]
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b); // prints "<name>, bureaucrat grade <grade>."

#endif
