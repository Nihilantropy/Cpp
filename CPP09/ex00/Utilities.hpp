#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <sstream>
#include <limits>
#include <iostream>

// Trim whitespace from both ends of a string
std::string trim(const std::string& str);

// Parse a string to a float, returning success/failure
bool stringToFloat(const std::string& str, float& result, std::string& errorMsg);

// Check if a date string is in the correct format (YYYY-MM-DD)
bool isValidDateFormat(const std::string& dateStr, std::string& errorMsg);

// Exit the program with an error message
void exitWithError(const std::string& message);

// Check if a file exists and is readable
bool fileExists(const std::string& filename);

#endif