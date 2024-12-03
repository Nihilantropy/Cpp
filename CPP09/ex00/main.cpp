#include "Date.hpp"
#include "database.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	std::map<Date, float> database;
	
	if (argc != 2)
		printErrorAndExit("wrong number of arguments");
	database = loadDatabase();
	printDatabase(database);

	std::string	inputFile;

	inputFile = argv[1];
	std::cout << inputFile << std::endl;
	return 0;
}