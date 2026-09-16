#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>

class Span
{
    public:
        Span(unsigned int n);
        Span(const Span &other);
        Span &operator=(const Span &other);
        ~Span();

        void addNumber(int value);
        int shortestSpan() const;
        int longestSpan() const;

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
