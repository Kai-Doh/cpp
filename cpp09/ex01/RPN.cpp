#include "RPN.hpp"
#include <sstream>
#include <stack>
#include <stdexcept>
#include <cctype>

bool RPN::isOperator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int RPN::apply(char op, int lhs, int rhs)
{
	switch (op)
	{
		case '+':
			return (lhs + rhs);
		case '-':
			return (lhs - rhs);
		case '*':
			return (lhs * rhs);
		case '/':
			if (rhs == 0)
				throw std::runtime_error("division by zero");
			return (lhs / rhs);
		default:
			throw std::runtime_error("unknown operator");
	}
}

int RPN::evaluate(const std::string& expression)
{
	std::istringstream iss(expression);
	std::stack<int> values;
	std::string token;

	while (iss >> token)
	{
		if (token.size() == 1 && std::isdigit(static_cast<unsigned char>(token[0])))
		{
			values.push(token[0] - '0');
		}
		else if (token.size() == 1 && isOperator(token[0]))
		{
			if (values.size() < 2)
				throw std::runtime_error("not enough operands");
			int rhs = values.top();
			values.pop();
			int lhs = values.top();
			values.pop();
			values.push(apply(token[0], lhs, rhs));
		}
		else
			throw std::runtime_error("invalid token: " + token);
	}

	if (values.size() != 1)
		throw std::runtime_error("malformed expression");
	return (values.top());
}
