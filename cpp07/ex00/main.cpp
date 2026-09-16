#include <iostream>
#include <string>
#include "whatever.hpp"

class Fixed
{
	public:
		Fixed(void) : _n(0) {}
		Fixed(int n) : _n(n) {}
		Fixed& operator=(Fixed& other) { _n = other._n; return (*this); }
		bool operator==(Fixed const& rhs) const { return (_n == rhs._n); }
		bool operator!=(Fixed const& rhs) const { return (_n != rhs._n); }
		bool operator>(Fixed const& rhs) const { return (_n > rhs._n); }
		bool operator<(Fixed const& rhs) const { return (_n < rhs._n); }
		bool operator>=(Fixed const& rhs) const { return (_n >= rhs._n); }
		bool operator<=(Fixed const& rhs) const { return (_n <= rhs._n); }
		int getN(void) const { return (_n); }
	private:
		int _n;
};

std::ostream& operator<<(std::ostream& o, const Fixed& f)
{
	o << f.getN();
	return (o);
}

int main()
{
	int a = 2;
	int b = 3;

	::swap(a, b);
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
	std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;

	std::string c = "chaine1";
	std::string d = "chaine2";

	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
	std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;

	std::cout << "min( 4, 4 ) = " << ::min(4, 4) << " (equal -> second param)" << std::endl;
	std::cout << "max( 4, 4 ) = " << ::max(4, 4) << " (equal -> second param)" << std::endl;

	std::cout << "-- custom class type --" << std::endl;
	Fixed e(2), f(4);

	::swap(e, f);
	std::cout << "e = " << e << ", f = " << f << std::endl;
	std::cout << "min( e, f ) = " << ::min(e, f) << std::endl;
	std::cout << "max( e, f ) = " << ::max(e, f) << std::endl;

	return (0);
}
