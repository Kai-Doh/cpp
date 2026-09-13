#ifndef DATA_HPP
#define DATA_HPP

#include <string>

// a non-empty structure used to prove serialize()/deserialize() round-trip correctly
struct Data
{
	int			id;
	std::string	label;
	double		weight;
};

#endif
