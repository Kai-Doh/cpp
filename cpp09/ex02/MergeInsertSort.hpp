#ifndef MERGEINSERTSORT_HPP
#define MERGEINSERTSORT_HPP

#include <vector>
#include <cstddef>

// Shared, container-agnostic sorting "brain": works out the correct final
// order (as a permutation of indices into 'allValues') using Ford-Johnson
// merge-insertion. Deliberately not templated on a container type -- it
// never touches vector/list/etc., only int indices and the value type T --
// so PmergeMe can implement the actual container-specific sort (how to
// physically rebuild a vector vs. a list) separately for each one, as the
// subject advises, while sharing only this pure "which order" logic.
template <typename T>
std::vector<size_t> fordJohnsonIndices(const std::vector<T>& allValues, std::vector<size_t> indices);

// exposed for unit testing the Jacobsthal ordering logic on its own
std::vector<size_t> jacobsthalInsertionOrder(size_t pairCount);

#include "MergeInsertSort.tpp"

#endif
