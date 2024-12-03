#ifndef DATE_HPP
#define DATE_HPP

#include <stdexcept>
#include <string>

class Date
{
public:
	Date();
	Date( const std::string& date );
	Date( const Date& other );
	Date& operator=( const Date& other );
	~Date();

	bool	operator<( const Date& other ) const;
	bool	operator>( const Date& other ) const;
	bool	operator==( const Date& other ) const;

	bool    isValidDate( void ) const;

	class	InvalidDateException : public std::exception {
	public:
		const char*	what() const throw();
	};

	int	getYear() const;
    int	getMonth() const;
    int	getDay() const;
	
private:
	int _year;
	int _month;
	int _day;

	void parseDate( const std::string& date);
};

std::ostream& operator<<(std::ostream& os, const Date& date);

#endif