#include "Utilities.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>

std::string trim(const std::string& str)
{
    if (str.empty()) 
        return "";
        
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
        
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

bool stringToFloat(const std::string& str, float& result, std::string& errorMsg)
{
    std::istringstream iss(str);
    
    // Try reading a float, then check if there's anything left in the stream
    if (!(iss >> result) || !(iss >> std::ws).eof()) {
        errorMsg = "could not convert '" + str + "' to a valid number";
        return false;
    }
    
    // Check for excessive values
    if (result > std::numeric_limits<float>::max() || 
        result < -std::numeric_limits<float>::max()) {
        errorMsg = "numeric value out of range";
        return false;
    }
    
    // Check for NaN or infinity
    if (result != result || result == std::numeric_limits<float>::infinity() || 
        result == -std::numeric_limits<float>::infinity()) {
        errorMsg = "numeric value is not valid (NaN or infinity)";
        return false;
    }
    
    return true;
}

bool isValidDateFormat(const std::string& dateStr, std::string& errorMsg)
{
    // Check basic length
    if (dateStr.size() != 10) {
        errorMsg = "invalid date format (expected YYYY-MM-DD)";
        return false;
    }
    
    // Check format: YYYY-MM-DD
    for (int i = 0; i < 10; ++i) {
        if ((i == 4 || i == 7) && dateStr[i] != '-') {
            errorMsg = "invalid date format (expected hyphens at positions 4 and 7)";
            return false;
        }
        if (i != 4 && i != 7 && !std::isdigit(dateStr[i])) {
            errorMsg = "invalid date format (expected digits except for hyphens)";
            return false;
        }
    }
    
    return true;
}

void exitWithError(const std::string& message)
{
    std::cerr << "Error: " << message << std::endl;
    exit(1);
}

bool fileExists(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    return file.good();
}