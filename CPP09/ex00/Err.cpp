#include "Err.hpp"
#include <iostream>
#include <cstdlib>

void printError(const std::string& message)
{
    std::cerr << "Error: " << message << std::endl;
}

void printErrorAndExit(const std::string& message)
{
    printError(message);
    exit(1);
}