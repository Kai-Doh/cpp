#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Base.hpp"

int main()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	for (int i = 0; i < 6; i++)
	{
		Base* p = generate();

		std::cout << "pointer identify: ";
		identify(p);
		std::cout << "reference identify: ";
		identify(*p);
		delete p;
	}
	return (0);
}
