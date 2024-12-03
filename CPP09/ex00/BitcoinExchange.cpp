#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange( const BitcoinExchange& other ) : _database(other._database) {}

BitcoinExchange& BitcoinExchange::operator=( const BitcoinExchange& other )
{
	if (this != &other)
		_database = other._database;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {};

/* getter */
std::map<Date, float>   BitcoinExchange::getDatabase( void ) const { return _database; };

/**
 * load data.svc into the BitcoingExchange object
 */
void	BitcoinExchange::loadDatabase(void)
{
	std::ifstream			file("data.csv");
	std::string				line;

	if (!file.is_open())
		printErrorAndExit("could not open file");
	
	// Skip the header line
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream   ss(line);
		std::string         dateStr;
		std::string         valueStr;

		std::getline(ss, dateStr, ',');
		std::getline(ss, valueStr);

		Date date(dateStr);
		float value = std::atof(valueStr.c_str());

		_database.insert(std::make_pair(date, value));
	}

	file.close();
}

void	BitcoinExchange::printDatabase()
{
	for (std::map<Date, float>::const_iterator it = _database.begin(); it != _database.end(); ++it) {
		std::cout << it->first << " => " << it->second << std::endl;
	}
}

std::string trim(const std::string& str)
{
	size_t start = str.find_first_not_of(" \t\r\n");
	size_t end = str.find_last_not_of(" \t\r\n");
	if (start == std::string::npos || end == std::string::npos) {
		return "";
	}
	return str.substr(start, end - start + 1);
}

bool isValidDate(const std::string& dateStr)
{
	if (dateStr.size() != 10) return false;  // Expected format is YYYY-MM-DD
	
	for (int i = 0; i < 10; ++i) {
		if ((i == 4 || i == 7) && dateStr[i] != '-') return false;
		if (i != 4 && i != 7 && !std::isdigit(dateStr[i])) return false;
	}
	return true;
}

void BitcoinExchange::printExchangeRate(const char* filename)
{
	std::ifstream file(filename);
	std::string line;

	if (!file.is_open())
		printErrorAndExit("Error: could not open file.");

	// Skip the header line
	std::getline(file, line);

	while (std::getline(file, line))
	{
		line = trim(line);

		if (line.empty()) {
            continue;  // Skip empty lines
        }
		std::stringstream ss(line);
		std::string dateStr, valueStr;

		if (std::getline(ss, dateStr, '|') && std::getline(ss, valueStr)) {
            dateStr = trim(dateStr);
            valueStr = trim(valueStr);
            
            // Additional checks for valid date and value
            if (!isValidDate(dateStr)) {
                std::cerr << "Error: bad input => " << dateStr << std::endl;
                continue;
            }
		}

		try
		{
			// Parse the date
			Date date(dateStr);

			// Parse the value
			float value = std::atof(valueStr.c_str());

			if (isValidValue(value) == false) {
				continue;
			}

			// Find the closest lower or equal date in the database
			std::map<Date, float>::const_iterator it = _database.lower_bound(date);
			if (it == _database.end() || it->first > date)
			{
				// If the lower_bound points to a date greater than input, go one step back
				if (it != _database.begin())
					--it;
				else
				{
					// If there's no valid date, skip this line
					std::cerr << "Error: no valid date found in database for input date." << std::endl;
					continue;
				}
			}

			// Multiply value by exchange rate
			float exchangeRate = it->second;
			float result = value * exchangeRate;

			// Print the result
			std::cout << dateStr << " => " << value << " = " << result << std::endl;
		}
		catch (const Date::InvalidDateException&)
		{
			std::cerr << "Error: bad input => " << dateStr << std::endl;
			continue;
		}
	}

	file.close();
}

bool	BitcoinExchange::isValidValue(float value)
{
	if (value < 0) {
		std::cerr << "Error: not a positive number " << std::endl;
		return false;
	}

	if (value > 1000) {
		std::cerr << "Error: value too large a number " << std::endl;
		return false;
	}
	
	return true;
}
