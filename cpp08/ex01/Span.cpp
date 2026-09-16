#include "Span.hpp"
#include <stdexcept>
#include <algorithm>

Span::Span() : _capacity(0)
{
}

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

void Span::addNumber(int value)
{
    if (_numbers.size() >= _capacity)
        throw std::length_error("Span is full");
    _numbers.push_back(value);
}

long long Span::shortestSpan() const
{
    if (_numbers.size() < 2)
        throw std::length_error("Not enough numbers to find a span");

    std::vector<int> sorted(_numbers);
    std::sort(sorted.begin(), sorted.end());

    long long shortest = static_cast<long long>(sorted[1]) - static_cast<long long>(sorted[0]);
    for (std::vector<int>::size_type i = 2; i < sorted.size(); ++i)
    {
        long long diff = static_cast<long long>(sorted[i]) - static_cast<long long>(sorted[i - 1]);
        if (diff < shortest)
            shortest = diff;
    }
    return (shortest);
}

long long Span::longestSpan() const
{
    if (_numbers.size() < 2)
        throw std::length_error("Not enough numbers to find a span");

    std::vector<int>::const_iterator minIt = std::min_element(_numbers.begin(), _numbers.end());
    std::vector<int>::const_iterator maxIt = std::max_element(_numbers.begin(), _numbers.end());
    return (static_cast<long long>(*maxIt) - static_cast<long long>(*minIt));
}
