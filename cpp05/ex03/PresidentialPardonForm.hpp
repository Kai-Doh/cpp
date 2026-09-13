#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

// pardons the target in the name of Zaphod Beeblebrox
class PresidentialPardonForm : public AForm
{
	public:
		PresidentialPardonForm(const std::string& target); // only the target is user-provided
		PresidentialPardonForm(const PresidentialPardonForm& other); // copy constructor
		PresidentialPardonForm& operator=(const PresidentialPardonForm& other); // assignment operator
		~PresidentialPardonForm(); // nothing to release

	protected:
		void action() const; // prints the pardon message

	private:
		std::string _target;
};

#endif
