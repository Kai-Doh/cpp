#ifndef ARRAY_HPP
#define ARRAY_HPP

// fixed-size, type-generic array with bounds-checked access and value semantics
template <typename T>
class Array
{
	public:
		Array(); // creates an empty (size 0) array
		Array(unsigned int n); // creates n elements, each value-initialized (0 for scalars)
		Array(const Array& other); // deep copy: allocates its own buffer
		Array& operator=(const Array& other); // deep copy assignment
		~Array(); // releases the owned buffer

		T&			operator[](unsigned int index); // bounds-checked access, throws on out-of-range index
		const T&	operator[](unsigned int index) const; // const bounds-checked access

		unsigned int size() const; // number of elements; does not modify the array

	private:
		T*				_data;
		unsigned int	_size;
};

#include "Array.tpp"

#endif
