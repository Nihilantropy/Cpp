#include "ScalarConverter.h"
#include <iostream>
#include <iomanip>

void printTestHeader(const std::string& testName) {
    std::cout << "\n=== Testing " << testName << " ===" << std::endl;
}

void runTest(const std::string& literal) {
    std::cout << "\nInput: \"" << literal << "\"" << std::endl;
    std::cout << "-------------------" << std::endl;
    ScalarConverter::convert(literal);
}

int main() {
    // Test char literals
    printTestHeader("Char Literals");
    runTest("a");
    runTest("Z");
    runTest("*");
    runTest(" ");  // space
    runTest("0");  // should be treated as int

    // Test int literals
    printTestHeader("Integer Literals");
    runTest("0");
    runTest("42");
    runTest("-42");
    runTest("+42");
    runTest("2147483647");    // INT_MAX
    runTest("-2147483648");   // INT_MIN
    runTest("2147483648");    // INT_MAX + 1
    runTest("-2147483649");   // INT_MIN - 1

    // Test float literals
    printTestHeader("Float Literals");
    runTest("0.0f");
    runTest("42.0f");
    runTest("-42.0f");
    runTest("+42.0f");
    runTest("42.42f");
    runTest(".0f");
    runTest("0.f");
    runTest("inff");
    runTest("+inff");
    runTest("-inff");
    runTest("nanf");
    runTest("340282346638528859811704183484516925440.0f");  // beyond float max
    
    // Test double literals
    printTestHeader("Double Literals");
    runTest("0.0");
    runTest("42.0");
    runTest("-42.0");
    runTest("+42.0");
    runTest("42.42");
    runTest(".0");
    runTest("0.");
    runTest("inf");
    runTest("+inf");
    runTest("-inf");
    runTest("nan");

    // Test invalid literals
    printTestHeader("Invalid Literals");
    runTest("");              // empty string
    runTest("abc");           // invalid string
    runTest("42.42.42");     // multiple dots
    runTest("42f");          // no decimal point in float
    runTest("42.42ff");      // multiple f
    runTest("42.42.f");      // invalid float format
    runTest("nanff");        // invalid nan
    runTest("infinff");      // invalid inf
    runTest("42.42.42");     // multiple dots
    runTest("+-42");         // invalid signs
    runTest("   42");        // leading spaces
    runTest("42   ");        // trailing spaces

    // Test edge cases
    printTestHeader("Edge Cases");
    runTest("0.0000000000000000000000000000000000000000000001f");
    runTest("340282346638528859811704183484516925440.000000f");
    runTest("-340282346638528859811704183484516925440.000000f");
    runTest("179769313486231570000000000000000000000000000000000000000000000000000"
            "000000000000000000000000000000000000000000000000000000000000000000000"
            "000000000000000000000000000000000000000000000000000000000000000000000"
            "000000000000000000000000000000000000000000000000000000000000000000000"
            ".0");  // very large number
    runTest("0.0000000000000000000000000000000000000000000000000000000000000000000"
            "000000000000000000000000000000000000000000000000000000000000000000000"
            "000000000000000000000000000000000000000000000000000000000000000000000"
            "000000000000000000000000000000000000000000000000000000000000000000001"); // very small number

    // Test special characters
    printTestHeader("Special Characters");
    runTest("\t");  // tab (should be invalid)
    runTest("\n");  // newline (should be invalid)
    runTest("@");   // special character
    runTest("$");   // special character
    runTest("#");   // special character

    return 0;
}