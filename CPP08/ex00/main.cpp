#include "easyfind.hpp"
#include <vector>
#include <list>
#include <iostream>

int main()
{
    try {
        std::cout << "Test with std::vector<int>" << std::endl;
        std::vector<int> vec;
        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);
        vec.push_back(40);

        // Test with element that exists
        std::vector<int>::iterator vec_it = easyfind(vec, 20);
        std::cout << "Found: " << *vec_it << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cout << "EVVIVA!" << std::endl;
        std::cerr << e.what() << std::endl;
    }

    std::cout << "----------------------------" << std::endl;

    try {
        std::cout << "Test with std::list<int>" << std::endl;
        std::list<int> lst;
        lst.push_back(100);
        lst.push_back(200);
        lst.push_back(300);

        // Test with element that exists
        std::list<int>::iterator list_it = easyfind(lst, 200);
        std::cout << "Found: " << *list_it << std::endl;

        // Test with element that does not exist
        list_it = easyfind(lst, 500);
        std::cout << "Found: " << *list_it << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
