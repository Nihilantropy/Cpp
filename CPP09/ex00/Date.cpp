#include "Date.hpp"
#include <ctime>
#include <sstream>
#include <iostream>

/* Default constructor */
Date::Date()
{
	std::time_t	now = std::time(NULL);
	std::tm* localTime = std::localtime(&now);

	_year = 1900 + localTime->tm_year;
	_month = 1 + localTime->tm_mon;
	_day = localTime->tm_mday;

	if (!isValidDate()) {
		throw InvalidDateException();
	}

	_dateValue = _year * 10000 + _month * 100 + _day;
};

/**
 * Parameterized Constructor
 * @param date The input date to validate.
 * 
 * @throw InvalidDateException If the date is invalid.
 */
Date::Date( const std::string& date )
{
	parseDate(date);

	if (!isValidDate()) {
		throw InvalidDateException();
	}
}

/* Copy Constructor */
Date::Date(const Date& other)
	: _year(other._year), _month(other._month), _day(other._day) {}

/* Assignment Operator */
Date& Date::operator=( const Date& other )
{
	if (this != &other)
	{
		_year = other._year;
		_month = other._month;
		_day = other._day;
	}
	return *this;
}

/* Destructor */
Date::~Date() {};

/**
 * Compare the internal date representation (e.g., YYYYMMDD or time_t)
 */
bool Date::operator<(const Date& other) const
{
    return this->_dateValue < other._dateValue;
}


/* Check if Date is Valid */
bool Date::isValidDate() const {
	if (_year < 0 || _month < 1 || _month > 12 || _day < 1) {
		return false;
	}

	int maxDay;
	switch (_month) {
		case 2:  // February
			maxDay = 28;
			if (_year % 4 == 0 && (_year % 100 != 0 || _year % 400 == 0)) {
				maxDay = 29;  // Leap year
			}
			break;
		case 4: case 6: case 9: case 11:  // Months with 30 days
			maxDay = 30;
			break;
		default:  // Months with 31 days
			maxDay = 31;
			break;
	}
	return _day <= maxDay;
}

/* Parse Date from String */
void Date::parseDate(const std::string& date) {
	std::istringstream dateStream(date);
	char delimiter;

	if (!(dateStream >> _year >> delimiter >> _month >> delimiter >> _day)
		|| (delimiter != '-' || _month < 1 || _month > 12 || _day < 1)
		|| date.empty()) {
		throw InvalidDateException();
	}
}

/* getter */
int	Date::getYear() const { return _year; }

int	Date::getMonth() const { return _month; }

int	Date::getDay() const { return _day; }

/* << operator overload */
std::ostream& operator<<(std::ostream& os, const Date& date) {
	os << date.getYear() << "-"
	<< (date.getMonth() < 10 ? "0" : "") << date.getMonth() << "-"
	<< (date.getDay() < 10 ? "0" : "") << date.getDay();
	return os;
}

/* Exception Description */
const char* Date::InvalidDateException::what() const throw() {
	return "Date is invalid! Try inputting a valid date in format: YYYY-MM-DD";
}