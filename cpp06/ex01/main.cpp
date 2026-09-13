#include <iostream>
#include "Serializer.hpp"

int main()
{
	Data original;
	original.id = 42;
	original.label = "hello";
	original.weight = 3.14;

	uintptr_t raw = Serializer::serialize(&original);
	Data* restored = Serializer::deserialize(raw);

	std::cout << "original address:  " << &original << std::endl;
	std::cout << "serialized value:  " << raw << std::endl;
	std::cout << "restored address:  " << restored << std::endl;

	if (restored == &original)
		std::cout << "OK: deserialize(serialize(ptr)) == ptr" << std::endl;
	else
		std::cout << "KO: pointers differ" << std::endl;

	std::cout << "restored->id = " << restored->id << ", label = " << restored->label
		<< ", weight = " << restored->weight << std::endl;

	return (0);
}
