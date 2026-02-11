#include "Fixed.hpp"
#include <iostream>

int main(void)
{
	std::cout << "========== TEST 1: Subject test ==========" << std::endl;
	Fixed a;
	Fixed b(a);
	Fixed c;

	c = b;

	std::cout << a.getRawBits() << std::endl;
	std::cout << b.getRawBits() << std::endl;
	std::cout << c.getRawBits() << std::endl;

	std::cout << "\n========== TEST 2: Orthodox Canonical Form ==========" << std::endl;
	std::cout << "Default constructor:" << std::endl;
	Fixed d;
	std::cout << "d raw bits: " << d.getRawBits() << std::endl;

	std::cout << "\nCopy constructor:" << std::endl;
	Fixed e(d);
	std::cout << "e raw bits: " << e.getRawBits() << std::endl;

	std::cout << "\nCopy assignment operator:" << std::endl;
	Fixed f;
	f = e;
	std::cout << "f raw bits: " << f.getRawBits() << std::endl;

	std::cout << "\n========== TEST 3: setRawBits test ==========" << std::endl;
	Fixed g;
	std::cout << "g initial: " << g.getRawBits() << std::endl;
	g.setRawBits(42);
	std::cout << "g after setRawBits(42): " << g.getRawBits() << std::endl;
	g.setRawBits(-10);
	std::cout << "g after setRawBits(-10): " << g.getRawBits() << std::endl;

	std::cout << "\n========== TEST 4: Copy independence ==========" << std::endl;
	Fixed original;
	original.setRawBits(100);
	Fixed copyTest(original);
	std::cout << "original: " << original.getRawBits() << ", copy: " << copyTest.getRawBits() << std::endl;
	original.setRawBits(200);
	std::cout << "After modifying original:" << std::endl;
	std::cout << "original: " << original.getRawBits() << ", copy: " << copyTest.getRawBits() << std::endl;

	std::cout << "\n========== TEST 5: Self-assignment ==========" << std::endl;
	Fixed h;
	h.setRawBits(50);
	std::cout << "h before self-assign: " << h.getRawBits() << std::endl;
	h = h;
	std::cout << "h after self-assign: " << h.getRawBits() << std::endl;

	std::cout << "\n========== TEST 6: Chain assignment ==========" << std::endl;
	Fixed x, y, z;
	x.setRawBits(999);
	z = y = x;
	std::cout << "x: " << x.getRawBits() << ", y: " << y.getRawBits() << ", z: " << z.getRawBits() << std::endl;

	std::cout << "\n========== END OF TESTS (destructors follow) ==========" << std::endl;
	return 0;
}
