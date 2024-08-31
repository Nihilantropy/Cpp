#include "../include/Harl.h"

int main(int argc, char **argv)
{
	Harl	harl;

	if (argc != 2)
	{
		std::cerr << "[ Usage ]:\n./harlFilter Level\nLevel can be:\nDEBUG\nINFO\nWARNING\nERROR" << std::endl;
		return 1;
	}

	harl.complain(argv[1]);

	return 0;
}
