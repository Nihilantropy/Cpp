#include "err.hpp"

void printErrorAndExit(const std::string& message)
{
    std::cerr << message << std::endl;
    exit(1);
}
