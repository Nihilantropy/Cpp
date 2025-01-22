#include "mainUtils.h"

/*	generate:
**	1) randomly instantiate one of 3 classe: A B C
**	2) return a pointer to the class
*/
Base*	generate( void )
{
	int	randomValue;

	randomValue = ((rand() % 3));
	std::cout << "Generated random value: " << randomValue << std::endl;
	switch (randomValue)
	{
		case 0: return new A();
		case 1: return new B();
		case 2: return new C();
		default: return NULL;
	}
}

/*	identify (pointer parameter):
**	Identifies the type of a pointer to the Base class.
**	Since classes A, B, and C inherit from Base, this function
**	allows us to determine which derived class the Base pointer points to.
**
**	The dynamic_cast allows us to safely downcast a Base pointer (p)
**	to one of its derived classes (A, B, or C), because the Base class 
**	has a virtual method, making it a polymorphic type.
**
**	If the cast fails, dynamic_cast returns a NULL pointer, indicating 
**	that the object is not of the expected type. The function uses 
**	this behavior to check each derived class sequentially.
**	If none of the casts succeed, the final else block prints "Unknown type".
*/
void	identify( Base* p )
{
	if (dynamic_cast<A*>(p))
		std::cout << "Type identified: A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "Type identified: B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "Type identified: C" << std::endl;
	else
		std::cout << "Unkown type" << std::endl;
}

/*	identify (reference parameter):
**	Identifies the type of a reference to a Base object.
**	Since classes A, B, and C inherit from Base, this function
**	allows us to determine which derived class the Base reference
**	actually refers to.
**
**	The dynamic_cast is used to safely downcast the Base reference (p)
**	to one of its derived classes (A, B, or C). Because a reference is used,
**	if the cast fails, dynamic_cast throws a `std::exception`.
**	This is different from using a pointer, where `dynamic_cast` would return `NULL` instead.
**
**	The function handles the `std::exception` in a try-catch block.
**	Each derived class is tested sequentially: if the cast to `A&` fails, the exception
**	is caught, and a new try block tests for `B&`. If that fails, the process is repeated for `C&`.
**
**	If all three casts fail, the function catches the final exception and prints an error message,
**	indicating that the type could not be identified as `A`, `B`, or `C`.
**
**	Note: Using a reference parameter is required to distinguish this implementation
**	from the pointer-based `identify` function, as references provide different casting behavior.
*/
void	identify( Base& p )
{
	try
	{
		A&	a = dynamic_cast<A&>(p);
		(void)a;
		std::cout << "A" << std::endl;
	}
	catch (const std::exception& e)
	{
		try
		{
			B&	b = dynamic_cast<B&>(p);
			(void)b;
			std::cout << "B" << std::endl;
		}
		catch (const std::exception& e)
		{
			try
			{
				C&	c = dynamic_cast<C&>(p);
				(void)c;
				std::cout << "C" << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}
}
