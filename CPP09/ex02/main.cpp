#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "Error: No sequence provided!" << std::endl;
		return 1;
	}

	PmergeMe pmergeMe;

	std::vector<int>	sequence;

	for (int i = 1; i < argc; ++i)
	{
		try
		{
			int num = std::atoi(argv[i]);
			if (num <= 0)
			{
				std::cerr << "Error: Only positive integers are allowed!" << std::endl;
				return 1;
			}
			sequence.push_back(num);
		}
		catch (...)
		{
			std::cerr << "Error: Invalid input!" << std::endl;
			return 1;
		}
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
