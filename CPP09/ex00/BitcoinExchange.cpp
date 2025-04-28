#include "BitcoinExchange.hpp"
#include "Utilities.hpp"
#include <iomanip>
#include <limits>

/* Constructors/Destructors */
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) 
    : _database(other._database) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
        _database = other._database;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

/* Getter */
std::map<Date, float> BitcoinExchange::getDatabase() const { 
    return _database; 
}

/**
 * Load data.csv into the BitcoinExchange object
 */
void BitcoinExchange::loadDatabase(const std::string& filename)
{
    if (!fileExists(filename)) {
        throw std::runtime_error("could not open database file: " + filename);
    }

    std::ifstream file(filename.c_str());
    std::string line;

    // Skip the header line
    if (!std::getline(file, line)) {
        throw std::runtime_error("database file is empty");
    }

    unsigned int lineCount = 1;
    while (std::getline(file, line))
    {
        lineCount++;
        line = trim(line);
        if (line.empty()) continue;

        std::istringstream ss(line);
        std::string dateStr;
        std::string valueStr;

        // Parse the line in format "date,value"
        if (!std::getline(ss, dateStr, ',') || !std::getline(ss, valueStr)) {
            std::cerr << "Warning: Invalid format in database at line " 
                     << lineCount << ": " << line << std::endl;
            continue;
        }

        dateStr = trim(dateStr);
        valueStr = trim(valueStr);

        try {
            // Parse date
            Date date(dateStr);
            
            // Parse value
            float value;
            std::string errorMsg;
            if (!stringToFloat(valueStr, value, errorMsg)) {
                std::cerr << "Warning: Invalid value in database at line " 
                         << lineCount << ": " << errorMsg << std::endl;
                continue;
            }

            // Add to database
            _database.insert(std::make_pair(date, value));
        }
        catch (const Date::InvalidDateException& e) {
            std::cerr << "Warning: Invalid date in database at line " 
                     << lineCount << ": " << e.what() << std::endl;
        }
    }

    file.close();
    
    if (_database.empty()) {
        throw std::runtime_error("No valid entries found in database");
    }
}

/**
 * Print the entire database for debugging
 */
void BitcoinExchange::printDatabase() const
{
    for (std::map<Date, float>::const_iterator it = _database.begin(); 
         it != _database.end(); ++it) {
        std::cout << it->first << " => " << it->second << std::endl;
    }
}

/**
 * Process a file containing exchange rates to calculate
 */
void BitcoinExchange::processExchangeFile(const std::string& filename)
{
    if (!fileExists(filename)) {
        throw std::runtime_error("could not open file: " + filename);
    }

    std::ifstream file(filename.c_str());
    std::string line;

    // Skip the header line
    if (!std::getline(file, line)) {
        throw std::runtime_error("input file is empty");
    }

    unsigned int lineNum = 1;
    while (std::getline(file, line))
    {
        lineNum++;
        processInputLine(line, lineNum);
    }

    file.close();
}

/**
 * Process a single line from the input file
 */
void BitcoinExchange::processInputLine(const std::string& line, unsigned int lineNum)
{
    std::string trimmedLine = trim(line);
    if (trimmedLine.empty()) {
        return; // Skip empty lines
    }

    std::string dateStr;
    float value;
    std::string errorMsg;

    // Parse line in "date | value" format
    if (!parseInputLine(trimmedLine, dateStr, value, errorMsg)) {
        std::cerr << "Error: " << errorMsg << " at line " << lineNum << std::endl;
        return;
    }

    // Check if value is valid
	if (!isValidValue(value, errorMsg)) {
		// Make sure errorMsg is not empty
		if (errorMsg.empty()) {
			errorMsg = "invalid value"; // Default message if empty
		}
		std::cerr << "Error: " << errorMsg << " at line " << lineNum << std::endl;
		return;
	}

    try {
        // Parse the date
        Date date(dateStr);
        
        // Get exchange rate
        float exchangeRate;
        if (!(getExchangeRate(date, errorMsg) > 0)) {
            std::cerr << "Error: " << errorMsg << " at line " << lineNum << std::endl;
            return;
        }
        exchangeRate = getExchangeRate(date, errorMsg);

        // Calculate and display result
        float result = value * exchangeRate;
        
        std::cout << std::fixed << std::setprecision(2);
        std::cout << dateStr << " => " << value << " = " << result << std::endl;
    }
    catch (const Date::InvalidDateException& e) {
        std::cerr << "Error: bad input => " << dateStr 
                 << " at line " << lineNum << std::endl;
    }
}

/**
 * Parse a line in format "date | value"
 */
bool BitcoinExchange::parseInputLine(const std::string& line, std::string& dateStr, 
                                    float& value, std::string& errorMsg) const
{
    std::istringstream ss(line);
    std::string valueStr;

    // Split by pipe character
    if (!std::getline(ss, dateStr, '|') || !std::getline(ss, valueStr)) {
        errorMsg = "bad input => " + line;
        return false;
    }

    dateStr = trim(dateStr);
    valueStr = trim(valueStr);

    // Check date format
    if (!isValidDateFormat(dateStr, errorMsg)) {
        errorMsg = "bad input => " + dateStr;
        return false;
    }

    // Parse value
    if (!stringToFloat(valueStr, value, errorMsg)) {
        errorMsg = "invalid value: " + errorMsg;
        return false;
    }

    return true;
}

/**
 * Check if a value is valid according to requirements
 */
bool BitcoinExchange::isValidValue(float value, std::string& errorMsg) const
{
    if (value < 0) {
        errorMsg = "not a positive number";
        return false;
    }

    if (value > 1000) {
        errorMsg = "value too large a number";
        return false;
    }

    if (value == 0) {
        errorMsg = "value must be greater than zero";
        return false;
    }
    
    return true;
}

/**
 * Get the exchange rate for a specific date
 */
float BitcoinExchange::getExchangeRate(const Date& date, std::string& errorMsg) const
{
    if (_database.empty()) {
        errorMsg = "database is empty";
        return -1;
    }
	
    // Find the closest lower or equal date in the database
    std::map<Date, float>::const_iterator it = _database.lower_bound(date);
    
    // If exact match
    if (it != _database.end() && !(date < it->first)) {
        return it->second;
    }
    
    // If the lower_bound points to a date greater than input, go one step back
    if (it == _database.end() || date < it->first)
    {
        if (it != _database.begin()) {
            --it;
            return it->second;
        }
        else {
            // Date is earlier than any in the database
            errorMsg = "no valid date found in database for input date";
            return -1;
        }
    }
    
    // Should never reach here
    errorMsg = "unexpected error finding exchange rate";
    return -1;
}

void BitcoinExchange::printDatabaseDates() const {
    std::cout << "Database contains " << _database.size() << " entries:" << std::endl;
    int count = 0;
    for (std::map<Date, float>::const_iterator it = _database.begin(); it != _database.end(); ++it) {
        std::cout << it->first << ", ";
        if (++count % 5 == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
}