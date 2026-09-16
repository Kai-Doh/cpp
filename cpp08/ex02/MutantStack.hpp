#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>
# include <deque>

// a std::stack that is also iterable: it inherits everything from std::stack,
// then exposes begin()/end() over the protected underlying container `c`
template <typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container>
{
    public:
        typedef typename Container::iterator iterator;

        MutantStack() : std::stack<T, Container>()
        {
        }

        MutantStack(const MutantStack &other) : std::stack<T, Container>(other)
        {
        }

        MutantStack &operator=(const MutantStack &other)
        {
            std::stack<T, Container>::operator=(other);
            return (*this);
        }

        virtual ~MutantStack()
        {
        }

        iterator begin() // iterator to the bottom of the stack
        {
            return (this->c.begin());
        }

        iterator end() // iterator past the top of the stack
        {
            return (this->c.end());
        }
};

#endif
