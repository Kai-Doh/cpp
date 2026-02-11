#include "Fixed.hpp"
#include <iostream>

int main(void)
{
	std::cout << "========== TEST 1: Subject test ==========" << std::endl;
	Fixed a;
	Fixed const b(Fixed(5.05f) * Fixed(2));

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;

	std::cout << b << std::endl;

	std::cout << Fixed::max(a, b) << std::endl;

	std::cout << "\n========== TEST 2: Comparison operators ==========" << std::endl;
	Fixed x(10);
	Fixed y(20);
	Fixed z(10);

	std::cout << "x=" << x << ", y=" << y << ", z=" << z << std::endl;
	std::cout << "x > y: " << (x > y ? "true" : "false") << std::endl;
	std::cout << "x < y: " << (x < y ? "true" : "false") << std::endl;
	std::cout << "x >= z: " << (x >= z ? "true" : "false") << std::endl;
	std::cout << "x <= z: " << (x <= z ? "true" : "false") << std::endl;
	std::cout << "x == z: " << (x == z ? "true" : "false") << std::endl;
	std::cout << "x != y: " << (x != y ? "true" : "false") << std::endl;
	std::cout << "x == y: " << (x == y ? "true" : "false") << std::endl;

	std::cout << "\n========== TEST 3: Arithmetic operators ==========" << std::endl;
	Fixed n1(10.5f);
	Fixed n2(3.5f);

	std::cout << "n1=" << n1 << ", n2=" << n2 << std::endl;
	std::cout << "n1 + n2 = " << (n1 + n2) << std::endl;
	std::cout << "n1 - n2 = " << (n1 - n2) << std::endl;
	std::cout << "n1 * n2 = " << (n1 * n2) << std::endl;
	std::cout << "n1 / n2 = " << (n1 / n2) << std::endl;

	std::cout << "\n========== TEST 4: Arithmetic with zero and negatives ==========" << std::endl;
	Fixed zero(0);
	Fixed neg(-5.5f);
	Fixed pos(5.5f);

	std::cout << "zero=" << zero << ", neg=" << neg << ", pos=" << pos << std::endl;
	std::cout << "pos + neg = " << (pos + neg) << std::endl;
	std::cout << "pos * zero = " << (pos * zero) << std::endl;
	std::cout << "neg * neg = " << (neg * neg) << std::endl;

	std::cout << "\n========== TEST 5: Increment/Decrement operators ==========" << std::endl;
	Fixed inc(5);
	std::cout << "Starting value: " << inc << std::endl;
	std::cout << "Pre-increment (++inc): " << ++inc << std::endl;
	std::cout << "Value after: " << inc << std::endl;
	std::cout << "Post-increment (inc++): " << inc++ << std::endl;
	std::cout << "Value after: " << inc << std::endl;
	std::cout << "Pre-decrement (--inc): " << --inc << std::endl;
	std::cout << "Value after: " << inc << std::endl;
	std::cout << "Post-decrement (inc--): " << inc-- << std::endl;
	std::cout << "Value after: " << inc << std::endl;

	std::cout << "\n========== TEST 6: min/max static functions ==========" << std::endl;
	Fixed small(1.5f);
	Fixed big(100.5f);

	std::cout << "small=" << small << ", big=" << big << std::endl;
	std::cout << "min(small, big): " << Fixed::min(small, big) << std::endl;
	std::cout << "max(small, big): " << Fixed::max(small, big) << std::endl;

	// Test with const references
	Fixed const constSmall(2.5f);
	Fixed const constBig(200.5f);
	std::cout << "const min: " << Fixed::min(constSmall, constBig) << std::endl;
	std::cout << "const max: " << Fixed::max(constSmall, constBig) << std::endl;

	std::cout << "\n========== TEST 7: Equal values ==========" << std::endl;
	Fixed eq1(42.42f);
	Fixed eq2(42.42f);
	std::cout << "eq1=" << eq1 << ", eq2=" << eq2 << std::endl;
	std::cout << "min(eq1, eq2): " << Fixed::min(eq1, eq2) << std::endl;
	std::cout << "max(eq1, eq2): " << Fixed::max(eq1, eq2) << std::endl;

	std::cout << "\n========== TEST 8: Chained operations ==========" << std::endl;
	Fixed result = Fixed(2) + Fixed(3) * Fixed(4);
	std::cout << "2 + 3 * 4 = " << result << " (should be 14)" << std::endl;

	result = (Fixed(2) + Fixed(3)) * Fixed(4);
	std::cout << "(2 + 3) * 4 = " << result << " (should be 20)" << std::endl;

	std::cout << "\n========== END OF TESTS ==========" << std::endl;
	return 0;
}
