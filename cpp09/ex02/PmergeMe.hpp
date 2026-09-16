#ifndef PMERGEME_HPP
# define PMERGEME_HPP

class PmergeMe
{
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void run(int argc, char **argv) const;
};

#endif
