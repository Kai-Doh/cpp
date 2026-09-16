#include "Span.hpp"
#include <stdexcept>
#include <algorithm>

Span::Span(unsigned int n) : _capacity(n)
{
}

Span::Span(const Span &other) : _capacity(other._capacity), _numbers(other._numbers)
{
}

Span &Span::operator=(const Span &other)
{
    if (this != &other)
    {
        _capacity = other._capacity;
        _numbers = other._numbers;
    }
    return (*this);
}

Span::~Span()
{
}

// rejects the number once the Span already holds _capacity elements
void Span::addNumber(int value)
{
    if (_numbers.size() >= _capacity)
        throw std::length_error("Span is full");
    _numbers.push_back(value);
}

// sorts a copy of the numbers, then the shortest span is always between two neighbours
int Span::shortestSpan() const
{
    if (_numbers.size() < 2)
        throw std::length_error("Not enough numbers to find a span");

    std::vector<int> sorted(_numbers);
    std::sort(sorted.begin(), sorted.end());

    int shortest = sorted[1] - sorted[0];
    for (std::vector<int>::size_type i = 2; i < sorted.size(); ++i)
    {
        int diff = sorted[i] - sorted[i - 1];
        if (diff < shortest)
            shortest = diff;
    }
    return (shortest);
}

// the longest span is simply max - min, no sorting needed
int Span::longestSpan() const
{
    if (_numbers.size() < 2)
        throw std::length_error("Not enough numbers to find a span");

    std::vector<int>::const_iterator minIt = std::min_element(_numbers.begin(), _numbers.end());
    std::vector<int>::const_iterator maxIt = std::max_element(_numbers.begin(), _numbers.end());
    return (*maxIt - *minIt);
}
