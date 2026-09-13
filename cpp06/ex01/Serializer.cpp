#include "Serializer.hpp"

Serializer::Serializer() {}
Serializer::Serializer(const Serializer& /* other */) {}
Serializer& Serializer::operator=(const Serializer& /* other */) { return (*this); }
Serializer::~Serializer() {}

// reinterprets the pointer's bit pattern as an unsigned integer, no value conversion involved
uintptr_t Serializer::serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

// reinterprets the integer's bit pattern back as a Data pointer
Data* Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data*>(raw));
}
