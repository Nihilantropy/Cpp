#ifndef SCALARCONVERTER_H
#define SCALARCONVERTER_H

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <cerrno>
#include <cmath>

class ScalarConverter
{
public:
	/*** static public method ***/
	static void convert(const std::string& literal);

private:
	/*** private constructor - static class ***/
	ScalarConverter();
	/*** copy constructor ***/
	ScalarConverter( const ScalarConverter& other );
	/*** assignment operator ***/
	ScalarConverter& operator=( const ScalarConverter& other );
	/*** destructor ***/
	~ScalarConverter();

	/*** private enum for type identification ***/
	enum Type
	{
		CHAR,
		INT,
		FLOAT,
		DOUBLE,
		INVALID
	};

	/*** private helper methods ***/
	/* type detection and validation */
	static Type detectType(const std::string& literal);
	static std::string getInvalidTypeReason(const std::string& literal);
	static bool isChar(const std::string& literal);
	static bool isInt(const std::string& literal);
	static bool isFloat(const std::string& literal);
	static bool isDouble(const std::string& literal);
	static bool isValidNumber(const std::string& str);

	/* pseudo-literal handling */
	static bool handlePseudoLiterals(const std::string& literal);
	static void printPseudoLiteral(const std::string& literal);

	/* conversion and printing */
	static void convertLiteral(const std::string& literal);
	static void printConversions(double value);
	static void printChar(double value);
	static void printInt(double value);
	static void printFloat(double value);
	static void printDouble(double value);
};

#endif