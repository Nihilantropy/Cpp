#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange( std::map<Date, float> exchangeMap ) : _excangeMap(exchangeMap) {}

BitcoinExchange::BitcoinExchange( const BitcoinExchange& other ) : _exchangeMap(other._exchangeMap) {}

BitcoinExchange& BitcoinExchange::operator=( const BitcoinExchange& other )
{
	if (this != &other)
		_exchangeMap = other._exchangeMap;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {};

std::map<Date, float>   BitcoinExchange::getExchangeMap( void ) const { return _exchangeMap };

bool	BitcoinExchange::isValidMap(void) const
{
	
	// Check if the value is valid
	if (value < 0) {
		std::cerr << "Error: not a positive number " << std::endl;
		continue;
	}

	if (value > 1000) {
		std::cerr << "Error: value too large a number " << std::endl;
		continue;
	}

}