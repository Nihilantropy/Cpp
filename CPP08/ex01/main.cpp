#include "Span.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

int main() {
	// Basic functionality test
	std::cout << "=== Basic Functionality Test ===" << std::endl;
	try {
		Span sp(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest Span: " << sp.longestSpan() << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// Test with range insertion
	std::cout << "\n=== Range Insertion Test ===" << std::endl;
	try {
		std::vector<int> nums;
		
		nums.push_back(2);
		nums.push_back(10);
		nums.push_back(0);
		nums.push_back(9);
		nums.push_back(-27671);
		nums.push_back(384);
		nums.push_back(122);
		nums.push_back(17);
		nums.push_back(1);
		Span sp2(10);
		sp2.addNumber(nums.begin(), nums.end());
		std::cout << "Shortest Span after range insert: " << sp2.shortestSpan() << std::endl;
		std::cout << "Longest Span after range insert: " << sp2.longestSpan() << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// Test with large numbers
	std::cout << "\n=== Large Numbers Test ===" << std::endl;
	try {
		Span sp3(5);
		sp3.addNumber(std::numeric_limits<int>::min());
		sp3.addNumber(std::numeric_limits<int>::max());
		sp3.addNumber(-1000000000);
		sp3.addNumber(1000000000);
		sp3.addNumber(0);
		std::cout << "Shortest Span: " << sp3.shortestSpan() << std::endl;
		std::cout << "Longest Span: " << sp3.longestSpan() << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// Edge case: not enough elements
	std::cout << "\n=== Not Enough Elements Test ===" << std::endl;
	try {
		Span sp4(2);
		sp4.addNumber(42);
		std::cout << "Shortest Span: " << sp4.shortestSpan() << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// Stress test with 100 million numbers
	std::cout << "\n=== Stress Test: 10 Million Numbers ===" << std::endl;
	try {
		const unsigned int size = 10000000;
		Span sp5(size);

		// Seed the random number generator
		std::srand(std::time(0));

		// Add random numbers
		for (unsigned int i = 0; i < size; ++i) {
			sp5.addNumber(std::rand());
		}

		std::cout << "Shortest Span: " << sp5.shortestSpan() << std::endl;
		std::cout << "Longest Span: " << sp5.longestSpan() << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// Test adding more numbers than capacity
	std::cout << "\n=== Overflow Test ===" << std::endl;
	try {
		Span sp6(3);
		sp6.addNumber(1);
		sp6.addNumber(2);
		sp6.addNumber(3);
		sp6.addNumber(4); // Should throw an exception
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
