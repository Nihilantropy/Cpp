#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#include <limits.h>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "Error: No sequence provided!" << std::endl;
		return 1;
	}

	PmergeMe pmergeMe;
	std::vector<int> sequence;

	for (int i = 1; i < argc; ++i)
	{
		std::string arg(argv[i]);
		std::istringstream iss(arg);
		std::string token;
		
		// If the argument contains spaces, split it and parse each token
		if (arg.find(' ') != std::string::npos)
		{
			while (iss >> token)
			{
				// Convert the token to an integer
				char* endptr;
				long num = std::strtol(token.c_str(), &endptr, 10);
				
				// Check if conversion was successful and the number is positive
				if (*endptr != '\0' || num <= 0)
				{
					std::cerr << "Error: Only positive integers are allowed! Invalid input: " << token << std::endl;
					return 1;
				}
				else if (num > INT_MAX) {
					std::cerr << "Error: value exceed MAX INT valeue" << std::endl;
					return 1;
				}
				sequence.push_back(static_cast<int>(num));
			}
		}
		else // Regular single number argument
		{
			// Convert the argument to an integer
			char* endptr;
			long num = std::strtol(arg.c_str(), &endptr, 10);
			
			// Check if conversion was successful and the number is positive
			if (*endptr != '\0' || num <= 0)
			{
				std::cerr << "Error: Only positive integers are allowed! Invalid input: " << arg << std::endl;
				return 1;
			}
			else if (num > INT_MAX) {
				std::cerr << "Error: value exceed MAX INT valeue" << std::endl;
				return 1;
			}
			sequence.push_back(static_cast<int>(num));
		}
	}

	// Check if we got any numbers after parsing
	if (sequence.empty())
	{
		std::cerr << "Error: No valid numbers provided" << std::endl;
		return 1;
	}

	try
	{
		pmergeMe.addSequence(sequence);
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	std::cout << "Testing with std::deque:" << std::endl;
	pmergeMe.sortAndDisplaySequence("Deque");

	std::cout << "\nTesting with std::vector:" << std::endl;
	pmergeMe.sortAndDisplaySequence("Vector");

	return 0;
}