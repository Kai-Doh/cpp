#include <iostream>
#include <vector>
#include <cstdlib>
#include "Span.hpp"

int main()
{
    Span sp(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;

    try
    {
        sp.addNumber(1);
    }
    catch (const std::exception &e)
    {
        std::cout << "adding to a full Span: " << e.what() << std::endl;
    }

    Span single(1);
    try
    {
        single.shortestSpan();
    }
    catch (const std::exception &e)
    {
        std::cout << "span with too few numbers: " << e.what() << std::endl;
    }

    std::vector<int> big;
    for (int i = 0; i < 10000; ++i)
        big.push_back(std::rand());

    Span bigSpan(10000);
    bigSpan.addNumber(big.begin(), big.end());
    std::cout << "10000 numbers, shortest: " << bigSpan.shortestSpan() << std::endl;
    std::cout << "10000 numbers, longest: " << bigSpan.longestSpan() << std::endl;

    return (0);
}
