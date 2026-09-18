#include <iostream>
#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
	try
	{
		PmergeMe sorter(argc, argv);
		sorter.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
