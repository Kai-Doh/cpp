#include "Fixed.hpp"
#include <cmath>

Fixed::Fixed() : _value(0)
{
}

Fixed::Fixed(const int n) : _value(n << _fractionalBits)
{
}

Fixed::Fixed(const float n) : _value(roundf(n * (1 << _fractionalBits)))
{
}

Fixed::Fixed(const Fixed& other)
{
	*this = other;
}

Fixed& Fixed::operator=(const Fixed& other)
{
	if (this != &other)
		_value = other.getRawBits();
	return *this;
}

Fixed::~Fixed()
{
}

int Fixed::getRawBits(void) const
{
	return _value;
}

void Fixed::setRawBits(int const raw)
{
	_value = raw;
}

float Fixed::toFloat(void) const
{
	return (float)_value / (1 << _fractionalBits);
}

int Fixed::toInt(void) const
{
	return _value >> _fractionalBits;
}

bool Fixed::operator>(const Fixed& other) const
{
	return _value > other._value;
}

bool Fixed::operator<(const Fixed& other) const
{
	return _value < other._value;
}

bool Fixed::operator>=(const Fixed& other) const
{
	return _value >= other._value;
}

bool Fixed::operator<=(const Fixed& other) const
{
	return _value <= other._value;
}

bool Fixed::operator==(const Fixed& other) const
{
	return _value == other._value;
}

bool Fixed::operator!=(const Fixed& other) const
{
	return _value != other._value;
}

Fixed Fixed::operator+(const Fixed& other) const
{
	Fixed result;
	result.setRawBits(_value + other._value);
	return result;
}

Fixed Fixed::operator-(const Fixed& other) const
{
	Fixed result;
	result.setRawBits(_value - other._value);
	return result;
}

Fixed Fixed::operator*(const Fixed& other) const
{
	Fixed result;
	result.setRawBits((_value * other._value) >> _fractionalBits);
	return result;
}

Fixed Fixed::operator/(const Fixed& other) const
{
	Fixed result;
	result.setRawBits((_value << _fractionalBits) / other._value);
	return result;
}

Fixed& Fixed::operator++()
{
	_value++;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed temp(*this);
	_value++;
	return temp;
}

Fixed& Fixed::operator--()
{
	_value--;
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed temp(*this);
	_value--;
	return temp;
}

Fixed& Fixed::min(Fixed& a, Fixed& b)
{
	return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
	return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b)
{
	return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
	return (a > b) ? a : b;
}

std::ostream& operator<<(std::ostream& out, const Fixed& fixed)
{
	out << fixed.toFloat();
	return out;
}
