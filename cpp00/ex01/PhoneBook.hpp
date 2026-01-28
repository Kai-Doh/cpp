#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"
# include <string>

class PhoneBook
{
private:
	Contact	_contacts[8];
	int		_contactCount;
	int		_oldestIndex;

	std::string	_truncate(const std::string &str) const;
	void		_printContact(int index) const;
	void		_printContactList() const;

public:
	PhoneBook();
	~PhoneBook();

	void	addContact();
	void	searchContact() const;
};

#endif
