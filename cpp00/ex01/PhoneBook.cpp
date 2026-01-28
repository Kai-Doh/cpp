#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <cctype>

PhoneBook::PhoneBook()
{
	contactCount = 0;
	oldestIndex = 0;
}

void PhoneBook::addContact()
{
	std::string input;
	int index = oldestIndex;

	std::cout << "Enter first name: ";
	if (!std::getline(std::cin, input) || input.empty())
	{
		std::cout << "Field cannot be empty!" << std::endl;
		return;
	}
	contacts[index].setFirstName(input);

	std::cout << "Enter last name: ";
	if (!std::getline(std::cin, input) || input.empty())
	{
		std::cout << "Field cannot be empty!" << std::endl;
		return;
	}
	contacts[index].setLastName(input);

	std::cout << "Enter nickname: ";
	if (!std::getline(std::cin, input) || input.empty())
	{
		std::cout << "Field cannot be empty!" << std::endl;
		return;
	}
	contacts[index].setNickname(input);

	std::cout << "Enter phone number: ";
	if (!std::getline(std::cin, input) || input.empty())
	{
		std::cout << "Field cannot be empty!" << std::endl;
		return;
	}
	for (size_t i = 0; i < input.length(); i++)
	{
		if (!isdigit(input[i]) && input[i] != '+')
		{
			std::cout << "Phone number can only contain digits and '+'!" << std::endl;
			return;
		}
	}
	contacts[index].setPhoneNumber(input);

	std::cout << "Enter darkest secret: ";
	if (!std::getline(std::cin, input) || input.empty())
	{
		std::cout << "Field cannot be empty!" << std::endl;
		return;
	}
	contacts[index].setDarkestSecret(input);

	std::cout << "Contact added!" << std::endl;

	oldestIndex = (oldestIndex + 1) % 8;
	if (contactCount < 8)
		contactCount++;
}

void PhoneBook::searchContact()
{
	if (contactCount == 0)
	{
		std::cout << "Phonebook is empty!" << std::endl;
		return;
	}

	// Print header
	std::cout << std::setw(10) << "Index" << "|";
	std::cout << std::setw(10) << "First Name" << "|";
	std::cout << std::setw(10) << "Last Name" << "|";
	std::cout << std::setw(10) << "Nickname" << std::endl;

	// Print each contact
	for (int i = 0; i < contactCount; i++)
	{
		std::string firstName = contacts[i].getFirstName();
		std::string lastName = contacts[i].getLastName();
		std::string nickname = contacts[i].getNickname();

		// Truncate if longer than 10 characters
		if (firstName.length() > 10)
			firstName = firstName.substr(0, 9) + ".";
		if (lastName.length() > 10)
			lastName = lastName.substr(0, 9) + ".";
		if (nickname.length() > 10)
			nickname = nickname.substr(0, 9) + ".";

		std::cout << std::setw(10) << i << "|";
		std::cout << std::setw(10) << firstName << "|";
		std::cout << std::setw(10) << lastName << "|";
		std::cout << std::setw(10) << nickname << std::endl;
	}

	// Ask for index
	std::cout << "Enter index: ";
	std::string input;
	if (!std::getline(std::cin, input))
		return;

	// Simple check: must be single digit 0-7
	if (input.length() != 1 || input[0] < '0' || input[0] > '7')
	{
		std::cout << "Invalid index!" << std::endl;
		return;
	}

	int index = input[0] - '0';
	if (index >= contactCount)
	{
		std::cout << "Invalid index!" << std::endl;
		return;
	}

	// Display the contact
	std::cout << "First Name: " << contacts[index].getFirstName() << std::endl;
	std::cout << "Last Name: " << contacts[index].getLastName() << std::endl;
	std::cout << "Nickname: " << contacts[index].getNickname() << std::endl;
	std::cout << "Phone Number: " << contacts[index].getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << contacts[index].getDarkestSecret() << std::endl;
}
