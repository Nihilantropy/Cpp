#include "err.hpp"

void printErrorAndExit(const std::string& message)
{
    std::cerr << "Error: " << message << std::endl;
    exit(1);
}
