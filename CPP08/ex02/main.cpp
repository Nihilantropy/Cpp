#include "MutantStack.hpp"
#include <iostream>
#include <list>

int main() {
	{
		std::cout << "=== Subject test ===" << std::endl;
		MutantStack<int> mstack;
		mstack.push(5);
		mstack.push(17);
		std::cout << mstack.top() << std::endl;
		mstack.pop();
		std::cout << mstack.top() << std::endl;
		std::cout << mstack.size() << std::endl;
		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		//[...]
		mstack.push(0);
		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
		std::stack<int> s(mstack);

		std::cout << "=== End of subject test ===" << std::endl;
	}
	{
		std::cout << "\n=== MutantStack Test ===" << std::endl;
		MutantStack<int> mstack;

		// Test basic stack operations
		mstack.push(5);
		mstack.push(17);
		std::cout << "Top element: " << mstack.top() << std::endl;
		mstack.pop();
		std::cout << "Stack size: " << mstack.size() << std::endl;

		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		mstack.push(0);

		// Test iteration
		std::cout << "\nIterating through MutantStack:" << std::endl;
		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		while (it != ite) {
			std::cout << *it << std::endl;
			++it;
		}

		// Compare with std::list
		std::cout << "\nComparing with std::list:" << std::endl;
		std::list<int> lst;
		lst.push_back(5);
		lst.push_back(3);
		lst.push_back(5);
		lst.push_back(737);
		lst.push_back(0);

		for (std::list<int>::iterator lit = lst.begin(); lit != lst.end(); ++lit) {
			std::cout << *lit << std::endl;
		}
	}

	return 0;
}
