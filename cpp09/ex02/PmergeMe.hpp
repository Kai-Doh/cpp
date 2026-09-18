#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <string>

// parses positive-integer CLI arguments, then sorts them with Ford-Johnson
// merge-insertion, implemented separately for std::vector and std::list,
// to compare their timings
class PmergeMe
{
	public:
		PmergeMe(); // default: empty sequence
		PmergeMe(int argc, char** argv); // throws std::runtime_error on any invalid argument
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		void run() const; // prints "Before:", "After:" and both container timings

	private:
		std::vector<int> _numbers;

		static bool parsePositiveInt(const std::string& token, int& value);
		static void printSequence(const std::string& label, const std::vector<int>& values);

		static void sortVector(std::vector<int>& values); // Ford-Johnson, rebuilt via random-access overwrite
		static void sortList(std::list<int>& values); // Ford-Johnson, rebuilt via clear() + push_back (no random access)
};

#endif
