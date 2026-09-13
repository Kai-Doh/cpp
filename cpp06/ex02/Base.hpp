#ifndef BASE_HPP
#define BASE_HPP

// polymorphic root: the virtual destructor is what enables dynamic_cast to work
class Base
{
	public:
		virtual ~Base(); // virtual so derived objects are destroyed correctly through a Base*
};

class A : public Base {}; // empty, only exists to be identified at runtime
class B : public Base {}; // empty, only exists to be identified at runtime
class C : public Base {}; // empty, only exists to be identified at runtime

Base*	generate(void); // randomly returns a new A, B or C as a Base*
void	identify(Base* p); // prints "A"/"B"/"C" for the pointed-to object
void	identify(Base& p); // prints "A"/"B"/"C" for the referenced object, without using a pointer

#endif
