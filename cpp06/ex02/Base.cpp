#include "Base.hpp"
#include <cstdlib>
#include <iostream>
#include <exception>

Base::~Base() {}

// picks A, B or C at random and hands it back through the common base pointer
Base* generate(void)
{
	switch (std::rand() % 3)
	{
		case 0:
			return (new A());
		case 1:
			return (new B());
		default:
			return (new C());
	}
}

// dynamic_cast on a pointer returns NULL on failure, no exception involved
void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown" << std::endl;
}

// dynamic_cast on a reference throws std::bad_cast on failure instead of returning NULL;
// catching it as std::exception avoids having to name/include <typeinfo> ourselves
void identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return ;
	}
	catch (const std::exception&) {}
	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return ;
	}
	catch (const std::exception&) {}
	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return ;
	}
	catch (const std::exception&)
	{
		std::cout << "Unknown" << std::endl;
	}
}
