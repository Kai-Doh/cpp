#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

int main()
{
    std::vector<int> v;
    for (int i = 0; i < 10; ++i)
        v.push_back(i * 2);

    std::cout << "vector:";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << " " << *it;
    std::cout << std::endl;

    try
    {
        std::vector<int>::iterator it = easyfind(v, 6);
        std::cout << "found 6 at position " << (it - v.begin()) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }

    try
    {
        easyfind(v, 7);
        std::cout << "found 7 (unexpected)" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "7 not found: " << e.what() << std::endl;
    }

    std::list<int> l;
    l.push_back(42);
    l.push_back(21);
    l.push_back(84);

    try
    {
        std::list<int>::iterator it = easyfind(l, 21);
        std::cout << "found " << *it << " in the list" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }

    return (0);
}
