#include <iostream>
#include <string>
#include "BitcoinExchange.hpp"
#include "Err.hpp"

int main(int argc, char **argv)
{    
    if (argc != 2) {
        printErrorAndExit("invalid number of arguments. Usage: ./btc <input_file>");
    }

    try {
        BitcoinExchange btc;

        // Load the database
        btc.loadDatabase("data.csv");

        // btc.printDatabaseDates();

        // Process the input file
        btc.processExchangeFile(argv[1]);
    }
    catch (const std::exception& e) {
        printError(e.what());
        return 1;
    }
    return 0;
}