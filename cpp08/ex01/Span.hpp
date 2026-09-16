#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>

class Span
{
    public:
        Span(unsigned int n); // sets the maximum capacity, starts empty
        Span(const Span &other); // copy constructor
        Span &operator=(const Span &other); // copy assignment
        ~Span(); // nothing to release, std::vector cleans itself up

        void addNumber(int value); // stores one number, throws once capacity is reached
        int shortestSpan() const; // smallest gap between any two stored numbers
        int longestSpan() const; // gap between the smallest and largest stored numbers

        // adds a whole range [first, last) in one call instead of looping addNumber() by hand
        template <typename InputIterator>
        void addNumber(InputIterator first, InputIterator last)
        {
            while (first != last)
            {
                addNumber(*first);
                ++first;
            }
        }

    private:
        unsigned int        _capacity;
        std::vector<int>    _numbers;
};

#endif
