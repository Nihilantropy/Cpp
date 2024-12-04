#include "PmergeMe.hpp"
#include <iostream>
#include <utility>
#include <algorithm>
#include <climits>
#include <stdexcept>
#include <set>

/* --- Canonical Form --- */

/* Constructor */
PmergeMe::PmergeMe() : _deque(0), _vector(0) {}

/* Copy Constructor */
PmergeMe::PmergeMe(const PmergeMe& other) : _deque(other._deque), _vector(other._vector) {}

/* Assignment Operator */
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_deque = other._deque;
		_vector = other._vector;
	}
	return *this;
}

/* Destructor */
PmergeMe::~PmergeMe() {}

/**
 * @brief Adds a sequence of positive integers to the deque and vector containers
 * 
 * We use a std::set to check for any duplicate number while adding the sequence into the
 * container
 * 
 * @param sequence A sequence of positive integers
 * @throws std::runtime_error If any integer in the sequence is negative
 */
void PmergeMe::addSequence(const std::vector<int>& sequence)
{
	std::set<int> seenValues;

	if (sequence.size() == 1)
		throw std::runtime_error("Error: cannot sort a single number");

	for (std::vector<int>::const_iterator it = sequence.begin(); it != sequence.end(); ++it)
	{
		if (*it < 0)
			throw std::runtime_error("Error: Only positive integers are allowed");

		if (seenValues.find(*it) != seenValues.end()) {
			throw std::runtime_error("Error: Duplicate values are not allowed");
		}

		if (*it > INT_MAX)
			throw std::runtime_error("Error: Input number cannot be greater than INT_MAX value");

		_deque.push_back(*it);
		_vector.push_back(*it);
		seenValues.insert(*it);
	}
}

/**
 * @brief Sorts the sequence stored in the deque using the merge-insert algorithm
 */
void	PmergeMe::sortSequenceWithDeque()
{
	std::deque<std::pair<int, int> >	pairs;

	pairAndSort(pairs, _deque);

	std::deque<int>	keys;
	std::deque<int>	values;

	extractKeysAndValues(pairs, keys, values);

	recursiveSort(keys);
	mergeKeysAndValues(keys, values);

	_deque = keys;
}

/**
 * @brief Sorts the sequence stored in the vector using the merge-insert algorithm
 */
void	PmergeMe::sortSequenceWithVector()
{
	std::vector<std::pair<int, int> >	pairs;

	pairAndSort(pairs, _vector);

	std::vector<int>	keys;
	std::vector<int>	values;

	extractKeysAndValues(pairs, keys, values);

	recursiveSort(keys);
	mergeKeysAndValues(keys, values);

	_vector = keys;
}

/**
 * @brief Pairs adjacent elements and sorts them by the first value in each pair
 * 
 * while the first element must always have the value pointed by the iterator,
 * the second element could not exist (last pair of an odd sequence). INT_MAX is
 * then used as a placeholder
 * 
 * @param pairs A container to store the pairs
 * @param container The original container of integers
 */
void	PmergeMe::pairAndSort(std::deque<std::pair<int, int> >& pairs, std::deque<int>& container)
{
	for (std::deque<int>::iterator it = container.begin(); it != container.end(); ++it)
	{
		int first = *it;
		++it;
		int second = (it != container.end()) ? *it : INT_MAX;

		if (first > second)
			pairs.push_back(std::make_pair(second, first));
		else
			pairs.push_back(std::make_pair(first, second));
	}
	std::sort(pairs.begin(), pairs.end());
}

void PmergeMe::pairAndSort(std::vector<std::pair<int, int> >& pairs, std::vector<int>& container)
{
	for (std::vector<int>::iterator it = container.begin(); it != container.end(); ++it)
	{
		int first = *it;
		++it;
		int second = (it != container.end()) ? *it : INT_MAX;

		if (first > second) {
			pairs.push_back(std::make_pair(second, first));
		} else {
			pairs.push_back(std::make_pair(first, second));
		}
	}
	std::sort(pairs.begin(), pairs.end());
}

/**
 * @brief Extracts keys and values from pairs into separate containers
 * 
 * @param pairs The sorted pairs of integers
 * @param keys A container to store the keys
 * @param values A container to store the values
 */
void PmergeMe::extractKeysAndValues(const std::deque<std::pair<int, int> >& pairs, std::deque<int>& keys, std::deque<int>& values)
{
	for (std::deque<std::pair<int, int> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		keys.push_back(it->first);
		values.push_back(it->second);
	}
}

void PmergeMe::extractKeysAndValues(const std::vector<std::pair<int, int> >& pairs, std::vector<int>& keys, std::vector<int>& values)
{
	for (std::vector<std::pair<int, int> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		keys.push_back(it->first);
		values.push_back(it->second);
	}
}

/**
 * @brief Recursively sorts the keys using the merge-insert technique
 * 
 * @param keys The keys to be recursively sorted
 */
void PmergeMe::recursiveSort(std::deque<int>& keys)
{
	if (keys.size() <= 1)
		return;

	std::deque<int>::iterator	middle = keys.begin() + keys.size() / 2;
	std::deque<int>				left(keys.begin(), middle);
	std::deque<int>				right(middle, keys.end());

	recursiveSort(left);
	recursiveSort(right);

	keys.clear();
	std::merge(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(keys));
}

void PmergeMe::recursiveSort(std::vector<int>& keys)
{
	if (keys.size() <= 1)
		return;

	std::vector<int>::iterator	middle = keys.begin() + keys.size() / 2;
	std::vector<int>			left(keys.begin(), middle);
	std::vector<int>			right(middle, keys.end());

	recursiveSort(left);
	recursiveSort(right);

	keys.clear();
	std::merge(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(keys));
}

/**
 * @brief Merges the sorted keys and values
 * 
 * @param keys The sorted keys
 * @param values The sorted values
 */
void PmergeMe::mergeKeysAndValues(std::deque<int>& keys, const std::deque<int>& values)
{
	for (std::deque<int>::const_iterator it = values.begin(); it != values.end(); ++it)
	{
		std::deque<int>::iterator pos = std::lower_bound(keys.begin(), keys.end(), *it);
		keys.insert(pos, *it);
	}
}

void PmergeMe::mergeKeysAndValues(std::vector<int>& keys, const std::vector<int>& values)
{
	for (std::vector<int>::const_iterator it = values.begin(); it != values.end(); ++it)
	{
		std::vector<int>::iterator pos = std::lower_bound(keys.begin(), keys.end(), *it);
		keys.insert(pos, *it);
	}
}

/**
 * @brief Displays the contents of the sorted sequence with a given container type
 * 
 * @param containerType A string indicating the type of container ("Deque" or "Vector")
 */
void PmergeMe::sortAndDisplaySequence(const std::string& containerType) const
{
	if (containerType == "Deque")
	{
		std::cout << "Before: ";
		for (std::deque<int>::const_iterator it = _deque.begin(); it != _deque.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		double timeDeque = measureTime(&PmergeMe::sortSequenceWithDeque);
		
		std::cout << "After: ";
		for (std::deque<int>::const_iterator it = _deque.begin(); it != _deque.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque: ";
		std::cout << timeDeque << " us" << std::endl;
	}
	else if (containerType == "Vector")
	{
		std::cout << "Before: ";
		for (std::vector<int>::const_iterator it = _vector.begin(); it != _vector.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		double timeVector = measureTime(&PmergeMe::sortSequenceWithVector);
		
		std::cout << "After: ";
		for (std::vector<int>::const_iterator it = _vector.begin(); it != _vector.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector: ";
		std::cout << timeVector << " us" << std::endl;
	}
}


/**
 * @brief Measures and displays the time taken to sort the container
 * 
 * @param sortMethod The sorting method to call on the container
 * @param container The container to be sorted
 * @return double The time taken to sort the container in microseconds
 */
double	PmergeMe::measureTime(void (PmergeMe::*sortMethod)()) const
{
	clock_t start = clock();

	// Sort using the member function that doesn't require parameters
	(const_cast<PmergeMe*>(this)->*sortMethod)();

	clock_t end = clock();

	return static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
}

/* utility */
void	PmergeMe::printRawSequence()
{
	std::cout << "Deque raw sequence" << std::endl;
	for (std::deque<int>::const_iterator it = _deque.begin(); it != _deque.end(); ++it)
		std::cout << *it << " ";
	std::cout << "\nVector raw sequence" << std::endl;
	for (std::vector<int>::const_iterator it = _vector.begin(); it != _vector.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}
