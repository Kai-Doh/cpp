#ifndef RPN_HPP
#define RPN_HPP

#include <string>

class RPN
{
	public:
		static int evaluate(const std::string& expression);

	private:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		static bool isOperator(char c);
		static int apply(char op, int lhs, int rhs);
};

#endif
