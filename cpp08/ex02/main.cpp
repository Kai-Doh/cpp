#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include "MutantStack.hpp"

int main()
{
    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);

    std::cout << mstack.top() << std::endl;

    mstack.pop();

    std::cout << mstack.size() << std::endl;

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }

    std::stack<int> s(mstack);
    std::cout << "converted to std::stack, size " << s.size() << std::endl;

    MutantStack<int> emptyStack;
    std::cout << "empty stack, begin == end: " << (emptyStack.begin() == emptyStack.end()) << std::endl;

    MutantStack<std::string> sstack;
    sstack.push("bottom");
    sstack.push("middle");
    sstack.push("top");
    for (MutantStack<std::string>::iterator sit = sstack.begin(); sit != sstack.end(); ++sit)
        std::cout << *sit << " ";
    std::cout << std::endl;

    MutantStack<int, std::vector<int> > vstack;
    vstack.push(1);
    vstack.push(2);
    vstack.push(3);
    for (MutantStack<int, std::vector<int> >::iterator vit = vstack.begin(); vit != vstack.end(); ++vit)
        std::cout << *vit << " ";
    std::cout << std::endl;

    return (0);
}
