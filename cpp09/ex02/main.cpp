#include <iostream>
#include <stdexcept>
#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    PmergeMe pm;

    try
    {
        pm.run(argc, argv);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }

    return (0);
}
