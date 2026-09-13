#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"

// creates a "<target>_shrubbery" file filled with ASCII trees
class ShrubberyCreationForm : public AForm
{
	public:
		ShrubberyCreationForm(const std::string& target); // only the target is user-provided
		ShrubberyCreationForm(const ShrubberyCreationForm& other); // copy constructor
		ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other); // assignment operator
		~ShrubberyCreationForm(); // nothing to release

	protected:
		void action() const; // writes ASCII trees into "<target>_shrubbery"

	private:
		std::string _target;
};

#endif
