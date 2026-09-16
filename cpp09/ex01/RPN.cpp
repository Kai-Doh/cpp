#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cctype>

RPN::RPN()
{
}

RPN::RPN(const RPN &other)
{
    (void)other;
}

RPN &RPN::operator=(const RPN &other)
{
    (void)other;
    return (*this);
}

RPN::~RPN()
{
}

static bool isOperator(const std::string &token)
{
    return (token.size() == 1 && (token[0] == '+' || token[0] == '-'
            || token[0] == '*' || token[0] == '/'));
}

long RPN::evaluate(const std::string &expression) const
{
    std::stack<long> values;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        if (isOperator(token))
        {
            if (values.size() < 2)
                throw std::runtime_error("Error");

            long b = values.top();
            values.pop();
            long a = values.top();
            values.pop();
            long result = 0;

            if (token[0] == '+')
                result = a + b;
            else if (token[0] == '-')
                result = a - b;
            else if (token[0] == '*')
                result = a * b;
            else
            {
                if (b == 0)
                    throw std::runtime_error("Error");
                result = a / b;
            }
            values.push(result);
        }
        else if (token.size() == 1 && std::isdigit(static_cast<unsigned char>(token[0])))
        {
            values.push(token[0] - '0');
        }
        else
            throw std::runtime_error("Error");
    }

    if (values.size() != 1)
        throw std::runtime_error("Error");

    return (values.top());
}
