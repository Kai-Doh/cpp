#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

PhoneBook::PhoneBook() : _contactCount(0), _oldestIndex(0)
{
}

PhoneBook::~PhoneBook()
{
}

std::string PhoneBook::_truncate(const std::string &str) const
{
	if (str.length() > 10)
		return str.substr(0, 9) + ".";
	return str;
}

void PhoneBook::_printContact(int index) const
{
	std::cout << "First Name: " << _contacts[index].getFirstName() << std::endl;
	std::cout << "Last Name: " << _contacts[index].getLastName() << std::endl;
	std::cout << "Nickname: " << _contacts[index].getNickname() << std::endl;
	std::cout << "Phone Number: " << _contacts[index].getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << _contacts[index].getDarkestSecret() << std::endl;
}

void PhoneBook::_printContactList() const
{
	std::cout << std::setw(10) << "Index" << "|";
	std::cout << std::setw(10) << "First Name" << "|";
	std::cout << std::setw(10) << "Last Name" << "|";
	std::cout << std::setw(10) << "Nickname" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;

	for (int i = 0; i < _contactCount; i++)
	{
		std::cout << std::setw(10) << i << "|";
		std::cout << std::setw(10) << _truncate(_contacts[i].getFirstName()) << "|";
		std::cout << std::setw(10) << _truncate(_contacts[i].getLastName()) << "|";
		std::cout << std::setw(10) << _truncate(_contacts[i].getNickname()) << std::endl;
	}
}

void PhoneBook::addContact()
{
	std::string input;

	std::cout << "Enter first name: ";
	std::getline(std::cin, input);
	if (std::cin.eof() || input.empty())
		return;
	_contacts[_oldestIndex].setFirstName(input);

	std::cout << "Enter last name: ";
	std::getline(std::cin, input);
	if (std::cin.eof() || input.empty())
		return;
	_contacts[_oldestIndex].setLastName(input);

	std::cout << "Enter nickname: ";
	std::getline(std::cin, input);
	if (std::cin.eof() || input.empty())
		return;
	_contacts[_oldestIndex].setNickname(input);

	std::cout << "Enter phone number: ";
	std::getline(std::cin, input);
	if (std::cin.eof() || input.empty())
		return;
	_contacts[_oldestIndex].setPhoneNumber(input);

	std::cout << "Enter darkest secret: ";
	std::getline(std::cin, input);
	if (std::cin.eof() || input.empty())
		return;
	_contacts[_oldestIndex].setDarkestSecret(input);

	_oldestIndex = (_oldestIndex + 1) % 8;
	if (_contactCount < 8)
		_contactCount++;
}

void PhoneBook::searchContact() const
{
	if (_contactCount == 0)
	{
		std::cout << "Phonebook is empty!" << std::endl;
		return;
	}

	_printContactList();

	std::cout << "Enter index to display: ";
	std::string input;
	std::getline(std::cin, input);

	if (std::cin.eof())
		return;

	std::stringstream ss(input);
	int index;
	ss >> index;

	if (ss.fail() || !ss.eof() || index < 0 || index >= _contactCount)
	{
		std::cout << "Invalid index!" << std::endl;
		return;
	}

	_printContact(index);
}
