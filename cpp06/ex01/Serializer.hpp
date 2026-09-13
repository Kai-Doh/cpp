#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <stdint.h>
#include "Data.hpp"

// utility class: cannot be instantiated, only offers static pointer <-> integer conversions
class Serializer
{
	public:
		static uintptr_t	serialize(Data* ptr); // converts a Data pointer to its integer representation
		static Data*		deserialize(uintptr_t raw); // converts an integer representation back to a Data pointer

	private:
		Serializer(); // not instantiable
		Serializer(const Serializer& other); // not instantiable
		Serializer& operator=(const Serializer& other); // not instantiable
		~Serializer(); // not instantiable
};

#endif
