#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"

// makes drilling noises, then robotomizes the target with a 50% success rate
class RobotomyRequestForm : public AForm
{
	public:
		RobotomyRequestForm(const std::string& target); // only the target is user-provided
		RobotomyRequestForm(const RobotomyRequestForm& other); // copy constructor
		RobotomyRequestForm& operator=(const RobotomyRequestForm& other); // assignment operator
		~RobotomyRequestForm(); // nothing to release

	protected:
		void action() const; // makes noise, then randomly succeeds or fails

	private:
		std::string _target;
};

#endif
