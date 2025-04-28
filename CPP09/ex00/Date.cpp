#include "Date.hpp"
#include "Utilities.hpp"
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>

// Default constructor - current date
Date::Date()
{
    std::time_t now = std::time(NULL);
    std::tm* localTime = std::localtime(&now);

    _year = 1900 + localTime->tm_year;
    _month = 1 + localTime->tm_mon;
    _day = localTime->tm_mday;

    if (!isValid()) {
        throw InvalidDateException("Current system date is invalid");
    }
}

// Constructor with date string
Date::Date(const std::string& date)
{
    std::string errorMsg;
    if (!isValidDateFormat(date, errorMsg)) {
        throw InvalidDateException("Invalid date format: " + errorMsg);
    }
    parseDate(date);
    if (!isValid()) {
        throw InvalidDateException("Date values out of range: " + date);
    }
}

// Copy constructor
Date::Date(const Date& other)
    : _year(other._year), _month(other._month), _day(other._day) {}

// Assignment operator
Date& Date::operator=(const Date& other)
{
    if (this != &other)
    {
        _year = other._year;
        _month = other._month;
        _day = other._day;
    }
    return *this;
}

// Destructor
Date::~Date() {}

// Less than operator
bool Date::operator<(const Date& other) const
{
    if (this->_year != other._year) {
        return this->_year < other._year;
    }
    if (this->_month != other._month) {
        return this->_month < other._month;
    }
    return this->_day < other._day;
}

// Greater than operator
bool Date::operator>(const Date& other) const
{
    return other < *this;
}

// Equality operator
bool Date::operator==(const Date& other) const
{
    return this->_year == other._year &&
           this->_month == other._month &&
           this->_day == other._day;
}

// Leap year check
bool Date::isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Check date validity
bool Date::isValid() const
{
    return isValidDate(_year, _month, _day);
}

// Static method to check if a date is valid
bool Date::isValidDate(int year, int month, int day)
{
    // Basic range check
    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    // Check day validity based on month
    int daysInMonth;
    switch (month) {
        case 2:  // February
            daysInMonth = isLeapYear(year) ? 29 : 28;
            break;
        case 4: case 6: case 9: case 11:  // 30-day months
            daysInMonth = 30;
            break;
        default:  // 31-day months
            daysInMonth = 31;
            break;
    }
    
    return day <= daysInMonth;
}

// Parse date from string
void Date::parseDate(const std::string& date)
{
    std::istringstream dateStream(date);
    char delimiter;

    if (!(dateStream >> _year >> delimiter >> _month >> delimiter >> _day)) {
        throw InvalidDateException("Failed to parse date: " + date);
    }
}

// Getters
int Date::getYear() const { return _year; }
int Date::getMonth() const { return _month; }
int Date::getDay() const { return _day; }

// Output operator
std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << date.getYear() << "-"
       << std::setw(2) << std::setfill('0') << date.getMonth() << "-"
       << std::setw(2) << std::setfill('0') << date.getDay();
    return os;
}

// InvalidDateException implementation
Date::InvalidDateException::InvalidDateException(const std::string& message)
    : _message(message) {}

Date::InvalidDateException::~InvalidDateException() throw() {}

const char* Date::InvalidDateException::what() const throw()
{
    return _message.c_str();
}