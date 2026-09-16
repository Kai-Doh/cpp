#ifndef PMERGEME_HPP
# define PMERGEME_HPP

class PmergeMe
{
    public:
        PmergeMe(); // stateless: nothing to initialize
        PmergeMe(const PmergeMe &other); // copy constructor
        PmergeMe &operator=(const PmergeMe &other); // copy assignment
        ~PmergeMe(); // nothing to release

        // parses argv, sorts it with Ford-Johnson via both a vector and a deque, prints before/after and timings
        void run(int argc, char **argv) const;
};

#endif
