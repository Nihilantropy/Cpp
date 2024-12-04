#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <string>
#include <stdlib.h>

class RPN
{
public:
	RPN();
	RPN( const RPN& other );
	RPN& operator=( const RPN& other );
	~RPN();

	/* public methods */
	int		evaluate( const std::string& expr );
	void	printResult( const std::string& expr );

private:
	std::stack<int>   _stack;

	/* private helper methods */
	void	processToken( const std::string& token );
	bool	isOperator( const std::string& token ) const;
	bool	isValidInteger(const std::string& token) const;
	int		performOperation( int a, int b, const std::string& op );
};

#endif