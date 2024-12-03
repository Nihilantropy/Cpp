#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include "Date.hpp"
#include <iostream>
#include <string>
#include <map>

class BitcoinExchange
{
public:
    BitcoinExchange( std::map<Date, float> exchangeMap );
    BitcoinExchange( const BitcoinExchange& other );
    BitcoinExchange& operator=( const BitcoinExchange& other );
    ~BitcoinExchange();

    std::map<Date, float>   getExchangeMap( void ) const;

    bool    isValidMap( void ) const;

private:
    std::map<Date, float>   _exchangeMap;
}


#endif
