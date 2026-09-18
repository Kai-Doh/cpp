#include "PmergeMe.hpp"
#include "MergeInsertSort.hpp"
#include <list>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <cstdlib>
#include <climits>
#include <cerrno>
#include <sys/time.h>

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(int argc, char** argv)
{
	if (argc < 2)
		throw std::runtime_error("no numbers given");

	for (int i = 1; i < argc; i++)
	{
		std::istringstream iss(argv[i]);
		std::string token;
		while (iss >> token)
		{
			int value;
			if (!parsePositiveInt(token, value))
				throw std::runtime_error("invalid argument: " + token);
			_numbers.push_back(value);
		}
	}
	if (_numbers.empty())
		throw std::runtime_error("no numbers given");
}

PmergeMe::PmergeMe(const PmergeMe& other) : _numbers(other._numbers)
{
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
		_numbers = other._numbers;
	return (*this);
}

PmergeMe::~PmergeMe()
{
}

bool PmergeMe::parsePositiveInt(const std::string& token, int& value)
{
	if (token.empty())
		return false;

	size_t start = (token[0] == '+') ? 1 : 0;
	if (start == token.size())
		return false;
	for (size_t i = start; i < token.size(); i++)
	{
		if (!std::isdigit(static_cast<unsigned char>(token[i])))
			return false;
	}

	errno = 0;
	char* end = 0;
	long parsed = std::strtol(token.c_str(), &end, 10);
	if (errno == ERANGE || parsed > INT_MAX || parsed <= 0)
		return false;

	value = static_cast<int>(parsed);
	return true;
}

void PmergeMe::printSequence(const std::string& label, const std::vector<int>& values)
{
	std::cout << label;
	for (size_t i = 0; i < values.size(); i++)
		std::cout << " " << values[i];
	std::cout << std::endl;
}

// vector has random access, so the sorted result can overwrite the
// existing elements in place, position by position.
void PmergeMe::sortVector(std::vector<int>& values)
{
	size_t n = values.size();
	if (n < 2)
		return;

	std::vector<int> allValues(values);
	std::vector<size_t> indices(n);
	for (size_t i = 0; i < n; i++)
		indices[i] = i;

	std::vector<size_t> sortedIndices = fordJohnsonIndices(allValues, indices);

	for (size_t i = 0; i < n; i++)
		values[i] = allValues[sortedIndices[i]];
}

// list has no random access, so there is no "overwrite position i"
// operation available -- the sorted result has to be rebuilt by clearing
// and appending in order instead.
void PmergeMe::sortList(std::list<int>& values)
{
	size_t n = values.size();
	if (n < 2)
		return;

	std::vector<int> allValues(values.begin(), values.end());
	std::vector<size_t> indices(n);
	for (size_t i = 0; i < n; i++)
		indices[i] = i;

	std::vector<size_t> sortedIndices = fordJohnsonIndices(allValues, indices);

	values.clear();
	for (size_t i = 0; i < n; i++)
		values.push_back(allValues[sortedIndices[i]]);
}

void PmergeMe::run() const
{
	printSequence("Before:", _numbers);

	std::vector<int> vecData(_numbers.begin(), _numbers.end());
	std::list<int> listData(_numbers.begin(), _numbers.end());
	struct timeval start;
	struct timeval end;

	gettimeofday(&start, 0);
	sortVector(vecData);
	gettimeofday(&end, 0);
	double vecTime = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

	printSequence("After:", vecData);

	gettimeofday(&start, 0);
	sortList(listData);
	gettimeofday(&end, 0);
	double listTime = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

	std::cout << "Time to process a range of " << _numbers.size()
		<< " elements with std::vector : " << vecTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _numbers.size()
		<< " elements with std::list : " << listTime << " us" << std::endl;
}
