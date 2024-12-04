#include "RPN.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <RPN expression>" << std::endl;
		return 1;
	}

	RPN rpn;

	rpn.printResult(argv[1]);

	return 0;
}