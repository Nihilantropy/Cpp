#ifndef DATE_HPP
#define DATE_HPP

#include <string>
#include <stdexcept>
#include <iostream>

class Date
{
public:
    // Constructors and destructor
    Date();
    Date(const std::string& date);
    Date(const Date& other);
    Date& operator=(const Date& other);
    ~Date();

    // Comparison operators
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator==(const Date& other) const;

    // Validation
    bool isValid() const;
    static bool isValidDate(int year, int month, int day);

    // Getters
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    
    // Exception class
    class InvalidDateException : public std::exception {
    private:
        std::string _message;
    public:
        InvalidDateException(const std::string& message = "Invalid date");
        virtual ~InvalidDateException() throw();
        virtual const char* what() const throw();
    };
    
private:
    int _year;
    int _month;
    int _day;

    void parseDate(const std::string& date);
    bool checkDateBounds() const;
    static bool isLeapYear(int year);
};

// Output operator
std::ostream& operator<<(std::ostream& os, const Date& date);

#endif