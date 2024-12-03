#include "database.hpp"

std::map<Date, float>	loadDatabase(void)
{
	std::map<Date, float>	database;
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

		try {
			// Attempt to parse the date
			Date date(dateStr);

			// Convert valueStr to float
			float value = std::atof(valueStr.c_str());

			database.insert(std::make_pair(date, value));
		}
		catch (const Date::InvalidDateException& e) {
			std::cerr << "Error: bad input => " << dateStr << std::endl;
			continue;
		}
	}

	file.close();
	return database;
}

void printDatabase(const std::map<Date, float>& database)
{
	for (std::map<Date, float>::const_iterator it = database.begin(); it != database.end(); ++it) {
		std::cout << it->first << " => " << it->second << std::endl;
	}
}