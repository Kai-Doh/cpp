#include "PmergeMe.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <cctype>
#include <cstddef>
#include <sys/time.h>

/*
** Ford-Johnson (merge-insertion) sort.
** Every element carries a globally unique `id`, assigned once when the input
** is read and never touched again by pairing, recursion, or insertion (those
** steps only ever copy whole Elem structs around). Each recursive call builds
** its own throwaway id -> local-pair-index table, valid only for the elements
** it is pairing right now, so an id keeps meaning "this exact input number"
** no matter how many recursion levels it passes through before being placed.
*/

namespace
{
    struct Elem
    {
        long        value;
        std::size_t id;
    };

    bool elemLess(const Elem &a, const Elem &b)
    {
        return (a.value < b.value);
    }

    /* Jacobsthal-ordered insertion sequence: the b-indices 2..m, grouped by
    ** Jacobsthal numbers and processed in descending order within each group.
    ** This is what keeps every binary-search window close to its worst case
    ** of log2(window) comparisons, the hallmark of Ford-Johnson. */
    std::vector<std::size_t> jacobsthalOrder(std::size_t m)
    {
        std::vector<std::size_t> order;
        if (m < 2)
            return (order);

        std::vector<std::size_t> jac;
        jac.push_back(0);
        jac.push_back(1);
        while (jac.back() < m)
            jac.push_back(jac[jac.size() - 1] + 2 * jac[jac.size() - 2]);

        std::size_t prev = 1;
        for (std::size_t k = 2; k < jac.size(); ++k)
        {
            std::size_t cur = jac[k];
            if (cur > m)
                cur = m;
            for (std::size_t idx = cur; idx > prev; --idx)
                order.push_back(idx);
            prev = cur;
            if (cur == m)
                break;
        }
        return (order);
    }

    std::vector<Elem> sortVec(std::vector<Elem> v, std::size_t totalN)
    {
        std::size_t n = v.size();
        if (n <= 1)
            return (v);

        bool hasLeftover = (n % 2 == 1);
        Elem leftover = Elem();
        if (hasLeftover)
        {
            leftover = v.back();
            v.pop_back();
        }

        std::size_t m = v.size() / 2;
        std::vector<Elem> smaller(m);
        std::vector<Elem> larger(m);
        std::vector<long> localIndexOf(totalN, -1);
        for (std::size_t i = 0; i < m; ++i)
        {
            Elem &x = v[2 * i];
            Elem &y = v[2 * i + 1];
            if (x.value <= y.value)
            {
                smaller[i] = x;
                larger[i] = y;
            }
            else
            {
                smaller[i] = y;
                larger[i] = x;
            }
            localIndexOf[larger[i].id] = static_cast<long>(i);
        }

        std::vector<Elem> chain = sortVec(larger, totalN);

        std::vector<Elem> result(chain);
        std::size_t idx0 = static_cast<std::size_t>(localIndexOf[chain[0].id]);
        result.insert(result.begin(), smaller[idx0]);

        std::vector<std::size_t> order = jacobsthalOrder(chain.size());
        for (std::size_t k = 0; k < order.size(); ++k)
        {
            std::size_t bi = order[k];
            long boundValue = chain[bi - 1].value;
            std::size_t idx = static_cast<std::size_t>(localIndexOf[chain[bi - 1].id]);
            Elem companion = smaller[idx];

            Elem boundKey;
            boundKey.value = boundValue;
            boundKey.id = 0;
            std::vector<Elem>::iterator bound =
                std::lower_bound(result.begin(), result.end(), boundKey, elemLess);

            std::vector<Elem>::iterator pos =
                std::upper_bound(result.begin(), bound, companion, elemLess);
            result.insert(pos, companion);
        }

        if (hasLeftover)
        {
            std::vector<Elem>::iterator pos =
                std::upper_bound(result.begin(), result.end(), leftover, elemLess);
            result.insert(pos, leftover);
        }

        return (result);
    }

    std::deque<Elem> sortDeq(std::deque<Elem> v, std::size_t totalN)
    {
        std::size_t n = v.size();
        if (n <= 1)
            return (v);

        bool hasLeftover = (n % 2 == 1);
        Elem leftover = Elem();
        if (hasLeftover)
        {
            leftover = v.back();
            v.pop_back();
        }

        std::size_t m = v.size() / 2;
        std::deque<Elem> smaller(m);
        std::deque<Elem> larger(m);
        std::vector<long> localIndexOf(totalN, -1);
        for (std::size_t i = 0; i < m; ++i)
        {
            Elem &x = v[2 * i];
            Elem &y = v[2 * i + 1];
            if (x.value <= y.value)
            {
                smaller[i] = x;
                larger[i] = y;
            }
            else
            {
                smaller[i] = y;
                larger[i] = x;
            }
            localIndexOf[larger[i].id] = static_cast<long>(i);
        }

        std::deque<Elem> chain = sortDeq(larger, totalN);

        std::deque<Elem> result(chain.begin(), chain.end());
        std::size_t idx0 = static_cast<std::size_t>(localIndexOf[chain[0].id]);
        result.insert(result.begin(), smaller[idx0]);

        std::vector<std::size_t> order = jacobsthalOrder(chain.size());
        for (std::size_t k = 0; k < order.size(); ++k)
        {
            std::size_t bi = order[k];
            long boundValue = chain[bi - 1].value;
            std::size_t idx = static_cast<std::size_t>(localIndexOf[chain[bi - 1].id]);
            Elem companion = smaller[idx];

            Elem boundKey;
            boundKey.value = boundValue;
            boundKey.id = 0;
            std::deque<Elem>::iterator bound =
                std::lower_bound(result.begin(), result.end(), boundKey, elemLess);

            std::deque<Elem>::iterator pos =
                std::upper_bound(result.begin(), bound, companion, elemLess);
            result.insert(pos, companion);
        }

        if (hasLeftover)
        {
            std::deque<Elem>::iterator pos =
                std::upper_bound(result.begin(), result.end(), leftover, elemLess);
            result.insert(pos, leftover);
        }

        return (result);
    }

    // wall-clock reading in microseconds, used to time each container's sort
    double nowMicroseconds()
    {
        struct timeval tv;
        gettimeofday(&tv, 0);
        return (static_cast<double>(tv.tv_sec) * 1000000.0 + static_cast<double>(tv.tv_usec));
    }

    // validates every argument is a plain positive integer, fills out, empty input is also an error
    bool parseArgs(int argc, char **argv, std::vector<long> &out)
    {
        for (int i = 1; i < argc; ++i)
        {
            std::string token(argv[i]);
            if (token.empty())
                return (false);

            std::string::size_type start = 0;
            if (token[0] == '+')
                start = 1;
            if (start >= token.size())
                return (false);

            for (std::string::size_type j = start; j < token.size(); ++j)
            {
                if (!std::isdigit(static_cast<unsigned char>(token[j])))
                    return (false);
            }

            long value = std::atol(token.c_str());
            if (value <= 0)
                return (false);
            out.push_back(value);
        }
        return (!out.empty());
    }
}

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    (void)other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    (void)other;
    return (*this);
}

PmergeMe::~PmergeMe()
{
}

void PmergeMe::run(int argc, char **argv) const
{
    std::vector<long> numbers;
    if (!parseArgs(argc, argv, numbers))
        throw std::runtime_error("Error");

    std::cout << "Before:";
    for (std::vector<long>::size_type i = 0; i < numbers.size(); ++i)
        std::cout << " " << numbers[i];
    std::cout << std::endl;

    std::size_t total = numbers.size();

    double vecStart = nowMicroseconds();
    std::vector<Elem> vecInput;
    for (std::size_t i = 0; i < total; ++i)
    {
        Elem e;
        e.value = numbers[i];
        e.id = i;
        vecInput.push_back(e);
    }
    std::vector<Elem> vecSorted = sortVec(vecInput, total);
    double vecEnd = nowMicroseconds();

    double deqStart = nowMicroseconds();
    std::deque<Elem> deqInput;
    for (std::size_t i = 0; i < total; ++i)
    {
        Elem e;
        e.value = numbers[i];
        e.id = i;
        deqInput.push_back(e);
    }
    std::deque<Elem> deqSorted = sortDeq(deqInput, total);
    double deqEnd = nowMicroseconds();

    std::cout << "After:";
    for (std::vector<Elem>::size_type i = 0; i < vecSorted.size(); ++i)
        std::cout << " " << vecSorted[i].value;
    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << numbers.size()
        << " elements with std::vector : " << (vecEnd - vecStart) << " us" << std::endl;
    std::cout << "Time to process a range of " << numbers.size()
        << " elements with std::deque : " << (deqEnd - deqStart) << " us" << std::endl;

    (void)deqSorted;
}
