#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <stdexcept>

BitcoinExchange::BitcoinExchange()
{
    loadDatabase("data.csv");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _rates(other._rates)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        _rates = other._rates;
    return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

std::string BitcoinExchange::trim(const std::string &s)
{
    std::string::size_type start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return ("");
    std::string::size_type end = s.find_last_not_of(" \t\r\n");
    return (s.substr(start, end - start + 1));
}

void BitcoinExchange::loadDatabase(const std::string &path)
{
    std::ifstream file(path.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open database.");

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::string::size_type comma = line.find(',');
        if (comma == std::string::npos)
            continue;
        std::string date = trim(line.substr(0, comma));
        std::string value = trim(line.substr(comma + 1));
        if (!isValidDate(date))
            continue;
        _rates[date] = std::atof(value.c_str());
    }
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
    if (date.size() != 10)
        return (false);
    if (date[4] != '-' || date[7] != '-')
        return (false);
    for (std::string::size_type i = 0; i < date.size(); ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(static_cast<unsigned char>(date[i])))
            return (false);
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 0 || month < 1 || month > 12 || day < 1)
        return (false);

    static const int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[month - 1];
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
        maxDay = 29;
    if (day > maxDay)
        return (false);

    return (true);
}

bool BitcoinExchange::isValidValue(const std::string &value, double &out)
{
    if (value.empty())
        return (false);

    std::string::size_type i = 0;
    if (value[i] == '-' || value[i] == '+')
        ++i;
    if (i >= value.size())
        return (false);

    bool sawDigit = false;
    bool sawDot = false;
    for (; i < value.size(); ++i)
    {
        if (value[i] == '.' && !sawDot)
            sawDot = true;
        else if (std::isdigit(static_cast<unsigned char>(value[i])))
            sawDigit = true;
        else
            return (false);
    }
    if (!sawDigit)
        return (false);

    out = std::atof(value.c_str());
    return (true);
}

double BitcoinExchange::getRate(const std::string &date) const
{
    std::map<std::string, double>::const_iterator it = _rates.lower_bound(date);

    if (it != _rates.end() && it->first == date)
        return (it->second);
    if (it == _rates.begin())
        throw std::runtime_error("Error: bad input => " + date);
    --it;
    return (it->second);
}

void BitcoinExchange::processFile(const std::string &path) const
{
    std::ifstream file(path.c_str());
    if (!file.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    bool first = true;
    while (std::getline(file, line))
    {
        if (first)
        {
            first = false;
            if (line == "date | value")
                continue;
        }
        if (line.empty())
            continue;

        std::string::size_type bar = line.find('|');
        if (bar == std::string::npos)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = trim(line.substr(0, bar));
        std::string valueStr = trim(line.substr(bar + 1));

        if (!isValidDate(date))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        double value;
        if (!isValidValue(valueStr, value))
        {
            std::cout << "Error: bad input => " << line << std::endl;
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
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}
