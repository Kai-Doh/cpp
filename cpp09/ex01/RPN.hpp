#ifndef RPN_HPP
# define RPN_HPP

# include <string>

class RPN
{
    public:
        RPN(); // stateless: nothing to initialize
        RPN(const RPN &other); // copy constructor
        RPN &operator=(const RPN &other); // copy assignment
        ~RPN(); // nothing to release

        long evaluate(const std::string &expression) const; // evaluates a reverse Polish notation expression
};

#endif
