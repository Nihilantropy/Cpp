#include "mainUtils.h"

int main()
{
	/* Seed the random number generator:
	** quote: "It is important to only invoke the srand call ONCE at the beginning of the program.
	** There is no need for repeat calls to seed the random number generator 
	** (in fact, it will make your number less evenly
	** distributed).
	** font: http://www.math.uaa.alaska.edu/~afkjm/csce211/handouts/RandomFunctions.pdf
	*/
	srand(static_cast<unsigned int>(time(NULL)));

	/* Generate a random instance of A, B, or C */
	Base* instance = generate();
	if (!instance)
	{
		std::cerr << "Error: Failed to generate instance" << std::endl;
		return 1;
	}
	/* Identify using pointer */
	std::cout << "Identifying using pointer: ";
	identify(instance);

	/* Identify using reference */
	std::cout << "Identifying using reference: ";
	identify(*instance);

	/* Clean up the allocated memory */
	delete instance;
	return 0;
}

