#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>

class AForm;

// has no name, no grade: its only skill is producing the form it's told to
class Intern
{
	public:
		Intern(); // no state to initialize
		Intern(const Intern& other); // copy constructor
		Intern& operator=(const Intern& other); // nothing to copy, but kept for OCF
		~Intern(); // nothing to release

		AForm* makeForm(const std::string& formName, const std::string& target) const; // builds the named form
};

#endif
