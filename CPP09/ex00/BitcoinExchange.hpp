#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include "Date.hpp"
#include "err.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <map>

class BitcoinExchange
{
public:
	BitcoinExchange();
	BitcoinExchange( const BitcoinExchange& other );
	BitcoinExchange& operator=( const BitcoinExchange& other );
	~BitcoinExchange();

	std::map<Date, float>   getDatabase( void ) const;

	void	loadDatabase( void );
	void	printDatabase( void );

	void	printExchangeRate( const char* filename );

private:
	std::map<Date, float>   _database;
	bool					isValidValue( float value );
};


#endif
