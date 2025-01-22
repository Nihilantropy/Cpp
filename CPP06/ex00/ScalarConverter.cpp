#include "ScalarConverter.h"
#include <cmath>
#include <cctype>

/**
 * @brief Converts string literal to scalar types (char, int, float, double) and displays results
 * 
 * @param literal Input string to convert. Valid formats: char ('a'), int (42), 
 *                float (42.0f, nanf), double (42.0, nan)
 * @return void Returns early on empty input, pseudo-literals, or after conversion
 */
void ScalarConverter::convert(const std::string& literal)
{
	if (literal.empty()) {
		std::cerr << "Error: empty literal." << std::endl;
		return;
	}

	// Check for non-printable characters first
    for (size_t i = 0; i < literal.length(); i++)
	{
        if (!std::isprint(literal[i]) && !std::isspace(literal[i]))
		{
            std::cerr << "Error: non-printable character detected." << std::endl;
            return;
        }
    }

	// Handle pseudo-literals first
	if (handlePseudoLiterals(literal))
		return;

	// Then try to detect and convert the type
	convertLiteral(literal);
}

/**
 * @brief Detects and processes pseudo-literals (nan, inf and their variants)
 * 
 * @param literal String to check against known pseudo-literals
 * @return true If literal is a pseudo-literal and was handled
 *         false If literal is not a pseudo-literal
 */
bool ScalarConverter::handlePseudoLiterals(const std::string& literal)
{
	const std::string pseudos[] = {
		"nan", "nanf", "+inf", "-inf", "+inff", "-inff", "inf", "inff"
	};

	for (size_t i = 0; i < sizeof(pseudos) / sizeof(pseudos[0]); ++i)
	{
		if (literal == pseudos[i]) {
			printPseudoLiteral(literal);
			return true;
		}
	}
	return false;
}

/**
 * @brief Displays scalar conversions for pseudo-literals (nan/inf variants)
 * 
 * @param literal The pseudo-literal to format and display ("nan", "inf", etc.)
 * @return void Prints char/int as impossible, formats float/double appropriately
 */
void ScalarConverter::printPseudoLiteral(const std::string& literal)
{
	// char and int are impossible for all pseudo-literals
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;

	// Handle nan cases
	if (literal == "nan" || literal == "nanf") {
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
		return;
	}

	// Handle infinity cases
	bool isNegative = (literal[0] == '-');
	std::cout << "float: " << (isNegative ? "-" : "+") << "inff" << std::endl;
	std::cout << "double: " << (isNegative ? "-" : "+") << "inf" << std::endl;
}

/**
 * @brief Converts detected literal type to double and prints all scalar conversions
 * 
 * @param literal String to convert based on its detected type
 * @return void Returns on error or after printing successful conversions
 *         Catches and reports any conversion exceptions
 */
void ScalarConverter::convertLiteral(const std::string& literal)
{
	double value = 0.0;
	Type type = detectType(literal);

    if (type == INVALID)
	{
        std::string reason = getInvalidTypeReason(literal);
        std::cerr << "Error: " << reason << std::endl;
        return ;
    }

	try {
		switch (type) {
			case CHAR:
				value = static_cast<double>(literal[0]);
				break;
			case INT:
				value = static_cast<double>(std::strtol(literal.c_str(), NULL, 10));
				break;
			case FLOAT:
				value = static_cast<double>(std::strtof(literal.c_str(), NULL));
				break;
			case DOUBLE:
				value = std::strtod(literal.c_str(), NULL);
				break;
			case INVALID:
				std::cerr << "Error: invalid literal type" << std::endl;
				return;
		}
		printConversions(value);
	}
	catch (const std::exception& e) {
		std::cerr << "Error during conversion: " << e.what() << std::endl;
	}
}

/**
 * @brief Determines specific reason why a literal is invalid
 * 
 * @param literal String to analyze for format errors
 * @return std::string Detailed error message explaining why the literal is invalid
 */
std::string ScalarConverter::getInvalidTypeReason(const std::string& literal)
{
    // Count decimal points
    int decimalPoints = 0;
    for (size_t i = 0; i < literal.length(); i++)
	{
        if (literal[i] == '.')
            decimalPoints++;
    }

    // Check for specific format issues
    if (decimalPoints > 1)
        return "invalid format: multiple decimal points";
    
    if (literal.find('f') != std::string::npos)
	{
        if (literal.find('f') != literal.length() - 1)
            return "invalid float format: 'f' must be at the end";
        if (decimalPoints == 0)
            return "invalid float format: missing decimal point";
    }

    if (literal.find_first_of("+-") != std::string::npos 
        && literal.find_first_of("+-") != literal.find_last_of("+-"))
        return "invalid format: multiple signs";

    if (std::isspace(literal[0]) || std::isspace(literal[literal.length() - 1]))
        return "invalid format: leading or trailing whitespace";

    for (size_t i = 0; i < literal.length(); i++)
	{
        if (!std::isdigit(literal[i]) && 
            literal[i] != '.' && 
            literal[i] != 'f' && 
            literal[i] != '+' && 
            literal[i] != '-' &&
            !std::isspace(literal[i]))
            return "invalid characters in literal";
    }

    return "invalid literal type";
}

/**
 * @brief Determines scalar type of input string
 * 
 * @param literal String to analyze for type detection
 * @return Type CHAR, INT, FLOAT, DOUBLE based on format match
 *         INVALID if no valid type detected
 */
ScalarConverter::Type ScalarConverter::detectType(const std::string& literal)
{
	if (isChar(literal))
		return CHAR;
	if (isInt(literal))
		return INT;
	if (isFloat(literal))
		return FLOAT;
	if (isDouble(literal))
		return DOUBLE;
	return INVALID;
}

bool ScalarConverter::isChar(const std::string& literal)
{
	return (literal.length() == 1 && 
			std::isprint(literal[0]) && 
			!std::isdigit(literal[0]));
}

bool ScalarConverter::isInt(const std::string& literal)
{
	if (literal.empty()) 
		return false;

	size_t start = 0;
	if (literal[0] == '+' || literal[0] == '-')
		start = 1;

	if (start == literal.length())
		return false;

	for (size_t i = start; i < literal.length(); ++i) {
		if (!std::isdigit(literal[i]))
			return false;
	}

	try {
		long num = std::strtol(literal.c_str(), NULL, 10);
		return (num >= std::numeric_limits<int>::min() && 
				num <= std::numeric_limits<int>::max());
	}
	catch (...) {
		return false;
	}
}

bool ScalarConverter::isFloat(const std::string& literal)
{
	if (literal.empty() || literal[literal.length() - 1] != 'f')
		return false;

	std::string withoutF = literal.substr(0, literal.length() - 1);
	return isValidNumber(withoutF);
}

bool ScalarConverter::isDouble(const std::string& literal)
{
	return isValidNumber(literal);
}

/** 
* @brief Validates if string represents a valid numerical format
* 
* @param str String to validate for numerical format
* @return true If string follows number format (optional sign, digits, optional single decimal)
*         false If empty, multiple decimals, or contains non-numeric characters
*/
bool ScalarConverter::isValidNumber(const std::string& str)
{
	if (str.empty())
		return false;

	size_t start = 0;
	bool hasDecimal = false;

	if (str[0] == '+' || str[0] == '-')
		start = 1;

	if (start == str.length())
		return false;

	for (size_t i = start; i < str.length(); ++i)
	{
		if (str[i] == '.')
		{
			if (hasDecimal)
				return false;
			hasDecimal = true;
		}
		else if (!std::isdigit(str[i]))
			return false;
	}

	return true;
}

void ScalarConverter::printConversions(double value)
{
	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}

void ScalarConverter::printChar(double value)
{
	std::cout << "char: ";
	if (value < 0 || value > 127 || std::isnan(value) || std::isinf(value))
		std::cout << "impossible";
	else if (!std::isprint(static_cast<int>(value)))
		std::cout << "Non displayable";
	else
		std::cout << "'" << static_cast<char>(value) << "'";
	std::cout << std::endl;
}

void ScalarConverter::printInt(double value)
{
	std::cout << "int: ";
	if (std::isnan(value) || std::isinf(value) ||
		value < std::numeric_limits<int>::min() || 
		value > std::numeric_limits<int>::max())
		std::cout << "impossible";
	else
		std::cout << static_cast<int>(value);
	std::cout << std::endl;
}

void ScalarConverter::printFloat(double value)
{
	std::cout << "float: ";
	if (std::isnan(value))
		std::cout << "nanf";
	else if (std::isinf(value))
		std::cout << (value < 0 ? "-" : "+") << "inff";
	else if (value < -std::numeric_limits<float>::max() || 
			value > std::numeric_limits<float>::max())
		std::cout << "impossible";
	else
		std::cout << std::fixed << std::setprecision(1) 
				<< static_cast<float>(value) << "f";
	std::cout << std::endl;
}

void ScalarConverter::printDouble(double value)
{
	std::cout << "double: ";
	if (std::isnan(value))
		std::cout << "nan";
	else if (std::isinf(value))
		std::cout << (value < 0 ? "-" : "+") << "inf";
	else
		std::cout << std::fixed << std::setprecision(1) << value;
	std::cout << std::endl;
}