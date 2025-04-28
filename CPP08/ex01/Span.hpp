#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

class Span
{
public:
	/*** parameterized constructor ***/
	Span(unsigned int N);
	/*** copy constructor ***/
	Span(const Span& other);
	/*** assignment operator ***/
	Span& operator=(const Span& other);
	/*** destructor ***/
	~Span();

	/*** public methods ***/

	/* add a single number to the Span (vector container) */
	void addNumber(int num);

	/* Template method to add a range of numbers using iterators */
	template <typename Iterator>
	void addNumber(Iterator begin, Iterator end)
	{
		if (_numbers.size() + std::distance(begin, end) > _maxSize) {
			std::stringstream ss;
			ss << "Adding these numbers will exceed the maximum size of " << _maxSize;
			throw std::overflow_error(ss.str());
		}
		_numbers.insert(_numbers.end(), begin, end);
	}

	/* Method to calculate the shortest span */
	int shortestSpan() const;

	/* Method to calculate the longest span */
	int longestSpan() const;

	/* Utility methods */
	unsigned int size() const;
	unsigned int capacity() const;
	bool empty() const;
	bool full() const;
	void clear();

	/* Access method with bounds checking */
	int at(unsigned int index) const;

	/* Fill span with random numbers */
	void fillRandomly(int min, int max);

	/* Print all numbers (for debugging) */
	void print() const;

private:
	std::vector<int> _numbers;
	unsigned int _maxSize;
};

#endif