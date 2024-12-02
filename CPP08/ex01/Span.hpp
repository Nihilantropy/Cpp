#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

class Span
{
public:
	/*** parameterized constructor ***/
	Span( unsigned int N );
	/*** copy constructor ***/
	Span( const Span& other );
	/*** assignment operator ***/
	Span& operator=(const Span& other );
	/*** destructor ***/
	~Span();

	/*** public methods ***/

	/* add a single number to the Span (vector container) */
	void	addNumber( int num );

	/* Template method to add a range of numbers using iterators */
	template <typename T>
    void	addNumber(T begin, T end)
	{
		if (_numbers.size() + std::distance(begin, end) > _maxSize) {
			throw std::overflow_error("Adding these numbers will exceed the maximum size");
		}
		_numbers.insert(_numbers.end(), begin, end);
	}

	/* Method to calculate the shortest span */
	int		shortestSpan() const;

	/* Method to calculate the longest span */
	int		longestSpan() const;


private:
	std::vector<int>	_numbers;
	unsigned int    	_maxSize;

};

#endif