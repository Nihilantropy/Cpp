#include <iostream>
#include <string>
#include "err.hpp"
#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{	
	if (argc != 2)
		printErrorAndExit("invalid number of arguments. Usage: ./btc <input_file>");

    try {
		(void)argv;
        BitcoinExchange btc;

        // Load the database
        btc.loadDatabase();

		//btc.printDatabase();

        // Process the input file
        btc.printExchangeRate(argv[1]);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
	return 0;
}