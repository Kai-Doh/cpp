#ifndef MERGEINSERTSORT_TPP
#define MERGEINSERTSORT_TPP

#include "MergeInsertSort.hpp"
#include <algorithm>

// Jacobsthal numbers: J(0)=0, J(1)=1, J(n)=J(n-1)+2*J(n-2).
// Returns the order (1-based, referring to the local pairing slot within
// the current recursion level) in which b2..bk should be inserted into the
// main chain, e.g. for pairCount=10: 3,2,5,4,11(clamped to 10),9,8,7,6.
// b1 is always inserted separately, at the front, before this is used.
inline std::vector<size_t> jacobsthalInsertionOrder(size_t pairCount)
{
	std::vector<size_t> order;
	if (pairCount < 2)
		return order;

	std::vector<size_t> jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	while (jacobsthal.back() < pairCount)
		jacobsthal.push_back(jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2]);

	size_t lowerBound = 1;
	for (size_t level = 2; level < jacobsthal.size() && lowerBound < pairCount; level++)
	{
		size_t upper = jacobsthal[level];
		if (upper > pairCount)
			upper = pairCount;
		for (size_t idx = upper; idx > lowerBound; idx--)
			order.push_back(idx);
		lowerBound = upper;
	}
	return order;
}

// Compares a value against the element an index refers to in a shared
// values table, so std::upper_bound can binary-search a vector of indices
// as if it were a vector of the values themselves.
template <typename T>
class IndexValueLess
{
	public:
		IndexValueLess() : _values(0) {}
		IndexValueLess(const std::vector<T>& values) : _values(&values) {}
		IndexValueLess(const IndexValueLess& other) : _values(other._values) {}
		IndexValueLess& operator=(const IndexValueLess& other)
		{
			if (this != &other)
				_values = other._values;
			return (*this);
		}
		~IndexValueLess() {}

		bool operator()(const T& value, size_t index) const
		{
			return (value < (*_values)[index]);
		}

	private:
		const std::vector<T>* _values;
};

// The actual Ford-Johnson (merge-insertion) sort, working on indices into
// a shared, never-copied 'allValues' table instead of on values directly.
// Recursing on indices (always std::vector<size_t>, regardless of T or
// recursion depth) keeps this a single, self-consistent template
// instantiation per T, and lets duplicate values be told apart
// unambiguously by their index identity when re-attaching each pair's
// smaller element after the "larger" half comes back recursively sorted.
template <typename T>
std::vector<size_t> fordJohnsonIndices(const std::vector<T>& allValues, std::vector<size_t> indices)
{
	size_t n = indices.size();
	if (n < 2)
		return indices;

	bool hasStray = (n % 2 == 1);
	size_t strayIndex = 0;
	if (hasStray)
	{
		strayIndex = indices.back();
		indices.pop_back();
		n--;
	}

	size_t pairCount = n / 2;
	std::vector<size_t> largerIdx(pairCount);
	std::vector<size_t> smallerIdx(pairCount);
	for (size_t i = 0; i < pairCount; i++)
	{
		size_t ia = indices[2 * i];
		size_t ib = indices[2 * i + 1];
		if (allValues[ia] < allValues[ib])
			std::swap(ia, ib);
		largerIdx[i] = ia;
		smallerIdx[i] = ib;
	}

	// sortedLarger[r] is a_(r+1): the larger element of rank r+1 among the
	// pairs, after recursively sorting. Kept immutable so that Jacobsthal
	// ranks can be mapped back to pairing slots even while 'chain' below
	// is being grown by insertions (which would otherwise shift ranks).
	std::vector<size_t> sortedLarger = fordJohnsonIndices(allValues, largerIdx);

	// recover, for each larger index, which local pairing slot (and thus
	// which smaller partner) it came from, independent of how the
	// recursive sort reordered it. Indexed directly by index identity
	// (unique across the whole shared 'allValues' table), so a plain
	// vector works as well as a map here and needs no extra container.
	std::vector<size_t> slotOfLargerIndex(allValues.size());
	for (size_t i = 0; i < pairCount; i++)
		slotOfLargerIndex[largerIdx[i]] = i;

	IndexValueLess<T> less(allValues);
	std::vector<size_t> chain(sortedLarger);

	// b1 is always smaller than a1 (the minimum of the sorted chain), so
	// it always belongs at the very front.
	size_t firstSlot = slotOfLargerIndex[sortedLarger[0]];
	chain.insert(chain.begin(), smallerIdx[firstSlot]);

	std::vector<size_t> order = jacobsthalInsertionOrder(pairCount);
	for (size_t k = 0; k < order.size(); k++)
	{
		size_t rank = order[k];
		size_t slot = slotOfLargerIndex[sortedLarger[rank - 1]];
		size_t candidate = smallerIdx[slot];
		std::vector<size_t>::iterator pos = std::upper_bound(chain.begin(), chain.end(), allValues[candidate], less);
		chain.insert(pos, candidate);
	}

	if (hasStray)
	{
		std::vector<size_t>::iterator pos = std::upper_bound(chain.begin(), chain.end(), allValues[strayIndex], less);
		chain.insert(pos, strayIndex);
	}

	return chain;
}

#endif
