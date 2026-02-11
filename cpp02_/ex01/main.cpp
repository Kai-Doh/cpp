#include "Fixed.hpp"
#include <iostream>

int main(void)
{
	std::cout << "========== TEST 1: Subject test ==========" << std::endl;
	Fixed a;
	Fixed const b(10);
	Fixed const c(42.42f);
	Fixed const d(b);

	a = Fixed(1234.4321f);

	std::cout << "a is " << a << std::endl;
	std::cout << "b is " << b << std::endl;
	std::cout << "c is " << c << std::endl;
	std::cout << "d is " << d << std::endl;

	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "d is " << d.toInt() << " as integer" << std::endl;

	std::cout << "\n========== TEST 2: Int constructor values ==========" << std::endl;
	Fixed zero(0);
	Fixed one(1);
	Fixed negative(-5);
	Fixed large(1000);
	std::cout << "0: " << zero << " (toInt: " << zero.toInt() << ")" << std::endl;
	std::cout << "1: " << one << " (toInt: " << one.toInt() << ")" << std::endl;
	std::cout << "-5: " << negative << " (toInt: " << negative.toInt() << ")" << std::endl;
	std::cout << "1000: " << large << " (toInt: " << large.toInt() << ")" << std::endl;

	std::cout << "\n========== TEST 3: Float constructor values ==========" << std::endl;
	Fixed f1(0.0f);
	Fixed f2(0.5f);
	Fixed f3(0.25f);
	Fixed f4(-3.14f);
	Fixed f5(100.999f);
	std::cout << "0.0f: " << f1 << " (toInt: " << f1.toInt() << ", toFloat: " << f1.toFloat() << ")" << std::endl;
	std::cout << "0.5f: " << f2 << " (toInt: " << f2.toInt() << ", toFloat: " << f2.toFloat() << ")" << std::endl;
	std::cout << "0.25f: " << f3 << " (toInt: " << f3.toInt() << ", toFloat: " << f3.toFloat() << ")" << std::endl;
	std::cout << "-3.14f: " << f4 << " (toInt: " << f4.toInt() << ", toFloat: " << f4.toFloat() << ")" << std::endl;
	std::cout << "100.999f: " << f5 << " (toInt: " << f5.toInt() << ", toFloat: " << f5.toFloat() << ")" << std::endl;

	std::cout << "\n========== TEST 4: Precision test ==========" << std::endl;
	std::cout << "Testing 8 fractional bits precision (1/256 = 0.00390625):" << std::endl;
	Fixed small(0.00390625f);
	std::cout << "0.00390625f: " << small << std::endl;
	Fixed smaller(0.001953125f);
	std::cout << "0.001953125f: " << smaller << " (might lose precision)" << std::endl;

	std::cout << "\n========== TEST 5: getRawBits/setRawBits ==========" << std::endl;
	Fixed raw;
	std::cout << "Default raw: " << raw.getRawBits() << std::endl;
	raw.setRawBits(256);  // 256 = 1.0 in fixed point with 8 fractional bits
	std::cout << "After setRawBits(256): " << raw << " (should be 1.0)" << std::endl;
	raw.setRawBits(512);  // 512 = 2.0
	std::cout << "After setRawBits(512): " << raw << " (should be 2.0)" << std::endl;

	std::cout << "\n========== TEST 6: Copy and assignment ==========" << std::endl;
	Fixed original(42.5f);
	Fixed copyConstructed(original);
	Fixed assigned;
	assigned = original;
	std::cout << "Original: " << original << std::endl;
	std::cout << "Copy constructed: " << copyConstructed << std::endl;
	std::cout << "Assigned: " << assigned << std::endl;

	std::cout << "\n========== END OF TESTS ==========" << std::endl;
	return 0;
}
