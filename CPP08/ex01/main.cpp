#include "Span.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

void testBasicFunctionality() {
    std::cout << "=== Basic Functionality Test ===" << std::endl;
    Span sp(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    
    sp.print();
    std::cout << "Is full: " << (sp.full() ? "yes" : "no") << std::endl;
    std::cout << "Size: " << sp.size() << std::endl;
    std::cout << "Capacity: " << sp.capacity() << std::endl;
    std::cout << "Value at index 2: " << sp.at(2) << std::endl;
    std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
    std::cout << "Longest Span: " << sp.longestSpan() << std::endl;
}

void testRandomNumbers() {
    std::cout << "\n=== Random Numbers Test ===" << std::endl;
    Span sp(10);
    sp.fillRandomly(1, 100);
    sp.print();
    std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
    std::cout << "Longest Span: " << sp.longestSpan() << std::endl;
}

void testLargeNumbers() {
    std::cout << "\n=== Large Numbers Test (10,000,00 numbers) ===" << std::endl;
    const unsigned int size = 1000000;
    Span sp(size);
    sp.fillRandomly(1, 1000000);
    
    std::cout << "Size: " << sp.size() << std::endl;
    std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
    std::cout << "Longest Span: " << sp.longestSpan() << std::endl;
}

void testRangeInsert() {
    std::cout << "\n=== Range Insertion Test ===" << std::endl;
    std::vector<int> nums;
    nums.push_back(2);
    nums.push_back(10);
    nums.push_back(0);
    nums.push_back(9);
    nums.push_back(-27671);
    nums.push_back(384);
    nums.push_back(122);
    
    Span sp(10);
    sp.addNumber(nums.begin(), nums.end());
    sp.print();
    std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
    std::cout << "Longest Span: " << sp.longestSpan() << std::endl;
}

void testErrorHandling() {
    std::cout << "\n=== Error Handling Test ===" << std::endl;
    
    try {
        std::cout << "Testing adding too many numbers:" << std::endl;
        Span sp(3);
        sp.addNumber(1);
        sp.addNumber(2);
        sp.addNumber(3);
        sp.addNumber(4); // Should throw an exception
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\nTesting not enough elements for span:" << std::endl;
        Span sp(5);
        sp.addNumber(42);
        std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\nTesting out of bounds access:" << std::endl;
        Span sp(3);
        sp.addNumber(1);
        sp.addNumber(2);
        std::cout << "Accessing index 5: " << sp.at(5) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

int main() {
    testBasicFunctionality();
    testRandomNumbers();
    testLargeNumbers();
    testRangeInsert();
    testErrorHandling();
    
    return 0;
}