#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <cstdlib>

static std::string trim(const std::string& s)
{
	size_t start = s.find_first_not_of(" \t\r\n");
	if (start == std::string::npos)
		return "";
	size_t end = s.find_last_not_of(" \t\r\n");
	return s.substr(start, end - start + 1);
}

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const std::string& databasePath)
{
	loadDatabase(databasePath);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _rates(other._rates)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_rates = other._rates;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

bool BitcoinExchange::isLeapYear(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

bool BitcoinExchange::isValidDate(const std::string& date)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (size_t i = 0; i < date.size(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return false;
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12 || day < 1)
		return false;

	static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int maxDay = daysInMonth[month - 1];
	if (month == 2 && isLeapYear(year))
		maxDay = 29;
	return (day <= maxDay);
}

bool BitcoinExchange::splitDateValue(const std::string& line, std::string& date, std::string& valueStr)
{
	size_t pos = line.find('|');
	if (pos == std::string::npos)
		return false;
	date = trim(line.substr(0, pos));
	valueStr = trim(line.substr(pos + 1));
	return (!date.empty() && !valueStr.empty());
}

bool BitcoinExchange::parseValue(const std::string& valueStr, double& value)
{
	std::istringstream iss(valueStr);
	char leftover;

	if (!(iss >> value))
		return false;
	if (iss >> leftover) // anything left over means trailing garbage
		return false;
	return true;
}

void BitcoinExchange::loadDatabase(const std::string& path)
{
	std::ifstream file(path.c_str());
	if (!file.is_open())
		throw std::runtime_error("could not open database file: " + path);

	std::string line;
	bool firstLine = true;
	while (std::getline(file, line))
	{
		line = trim(line);
		if (line.empty())
			continue;
		if (firstLine)
		{
			firstLine = false;
			if (line == "date,exchange_rate")
				continue;
		}

		size_t pos = line.find(',');
		if (pos == std::string::npos)
			continue;
		std::string date = trim(line.substr(0, pos));
		std::string rateStr = trim(line.substr(pos + 1));
		double rate;
		if (!isValidDate(date) || !parseValue(rateStr, rate))
			continue;
		_rates[date] = rate;
	}
	if (_rates.empty())
		throw std::runtime_error("database is empty or unreadable: " + path);
}

double BitcoinExchange::getRate(const std::string& date) const
{
	std::map<std::string, double>::const_iterator it = _rates.lower_bound(date);

	if (it != _rates.end() && it->first == date)
		return it->second;
	if (it == _rates.begin())
		throw std::runtime_error("no rate available on or before " + date);
	--it;
	return it->second;
}

void BitcoinExchange::processFile(const std::string& inputPath) const
{
	std::ifstream file(inputPath.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	bool firstLine = true;
	while (std::getline(file, line))
	{
		std::string trimmed = trim(line);
		if (trimmed.empty())
			continue;
		if (firstLine)
		{
			firstLine = false;
			if (trimmed == "date | value")
				continue;
		}

		std::string date;
		std::string valueStr;
		double value;

		if (!splitDateValue(trimmed, date, valueStr) || !isValidDate(date) || !parseValue(valueStr, value))
		{
			std::cout << "Error: bad input => " << trimmed << std::endl;
			continue;
		}
		if (value < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}

		try
		{
			double rate = getRate(date);
			std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
}
