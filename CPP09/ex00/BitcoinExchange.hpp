#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include "Date.hpp"
#include "Utilities.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <map>
#include <stdexcept>

class BitcoinExchange
{
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    std::map<Date, float> getDatabase() const;

    // Load the exchange rate database from a file
    void loadDatabase(const std::string& filename = "data.csv");
    
    // Process and print exchange rate calculations from input file
    void processExchangeFile(const std::string& filename);
    
    // Print the entire database content (for debugging)
    void printDatabase() const;

	void printDatabaseDates() const;

private:
    std::map<Date, float> _database;
    
    // Process a single line from the input file
    void processInputLine(const std::string& line, unsigned int lineNum);
    
    // Check if a value is within valid range
    bool isValidValue(float value, std::string& errorMsg) const;
    
    // Parse a line in format "date | value"
    bool parseInputLine(const std::string& line, std::string& dateStr, float& value, std::string& errorMsg) const;
    
    // Get the exchange rate for a specific date
    float getExchangeRate(const Date& date, std::string& errorMsg) const;
};

#endif