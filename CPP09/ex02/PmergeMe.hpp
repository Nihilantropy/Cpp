#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <utility>
#include <ctime>
#include <string>

class PmergeMe
{
public:
	PmergeMe();
	PmergeMe( const PmergeMe& other );
	PmergeMe& operator=( const PmergeMe& other );
	~PmergeMe();

	void	addSequence(const std::vector<int>& sequence);
	void	sortSequenceWithDeque();
	void	sortSequenceWithVector();
	void	sortAndDisplaySequence(const std::string& containerType) const;

	/* utility */
	void	printRawSequence();

private:

	std::deque<int>		_deque;
	std::vector<int>	_vector;

	bool	_oddSequence;

	/* deque container */
	void	pairAndSort(std::deque<std::pair<int, int> >& pairs, std::deque<int>& container);
	void	extractKeysAndValues(const std::deque<std::pair<int, int> >& pairs, std::deque<int>& keys, std::deque<int>& values);
	void	recursiveSort(std::deque<int>& keys);
	void	mergeKeysAndValues(std::deque<int>& keys, const std::deque<int>& values);

	/* vector container */
	void	pairAndSort(std::vector<std::pair<int, int> >& pairs, std::vector<int>& container);
	void	extractKeysAndValues(const std::vector<std::pair<int, int> >& pairs, std::vector<int>& keys, std::vector<int>& values);
	void	recursiveSort(std::vector<int>& keys);
	void	mergeKeysAndValues(std::vector<int>& keys, const std::vector<int>& values);

	double	measureTime(void (PmergeMe::*sortMethod)()) const;
};

#endif