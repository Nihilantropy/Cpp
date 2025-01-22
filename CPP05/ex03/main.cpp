#include "Bureaucrat.h"
#include "ShrubberyCreationForm.h"
#include "RobotomyRequestForm.h"
#include "PresidentialPardonForm.h"
#include "Intern.h"
#include <iostream>

void testInternFormCreation() {
    std::cout << "\n=== Testing Intern Form Creation ===\n" << std::endl;
    
    Intern intern;
    AForm* form = NULL;

    // Test successful form creation
    try {
        form = intern.makeForm("robotomy request", "Bender");
        std::cout << "Successfully created form: " << *form << std::endl;
        delete form;
        
        form = intern.makeForm("presidential pardon", "Alice");
        std::cout << "Successfully created form: " << *form << std::endl;
        delete form;
        
        form = intern.makeForm("shrubbery creation", "Garden");
        std::cout << "Successfully created form: " << *form << std::endl;
        delete form;
    }
    catch (std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        if (form)
            delete form;
    }

    // Test invalid form name
    try {
        form = intern.makeForm("invalid form", "Target");
        delete form;  // Should not reach here
    }
    catch (std::exception& e) {
        std::cout << "Expected error caught: " << e.what() << std::endl;
    }
}

void testFormExecution() {
    std::cout << "\n=== Testing Form Execution ===\n" << std::endl;
    
    Intern intern;
    Bureaucrat highGrade("HighGrade", 1);
    Bureaucrat lowGrade("LowGrade", 150);
    
    // Test RobotomyRequestForm
    try {
        AForm* robotomyForm = intern.makeForm("robotomy request", "R2D2");
        std::cout << "\nTesting RobotomyRequestForm:" << std::endl;
        
        // Test unsigned form execution
        try {
            lowGrade.executeForm(*robotomyForm);
        }
        catch (std::exception& e) {
            std::cout << "Expected error caught: " << e.what() << std::endl;
        }
        
        // Test signing and execution
        highGrade.signForm(*robotomyForm);
        highGrade.executeForm(*robotomyForm);
        delete robotomyForm;
    }
    catch (std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
    
    // Test PresidentialPardonForm
    try {
        AForm* pardonForm = intern.makeForm("presidential pardon", "Zaphod");
        std::cout << "\nTesting PresidentialPardonForm:" << std::endl;
        
        // Test with low grade bureaucrat
        try {
            lowGrade.signForm(*pardonForm);
        }
        catch (std::exception& e) {
            std::cout << "Expected error caught: " << e.what() << std::endl;
        }
        
        // Test with high grade bureaucrat
        highGrade.signForm(*pardonForm);
        highGrade.executeForm(*pardonForm);
        delete pardonForm;
    }
    catch (std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
    
    // Test ShrubberyCreationForm
    try {
        AForm* shrubForm = intern.makeForm("shrubbery creation", "Home");
        std::cout << "\nTesting ShrubberyCreationForm:" << std::endl;
        
        Bureaucrat mediumGrade("MediumGrade", 137);
        mediumGrade.signForm(*shrubForm);
        mediumGrade.executeForm(*shrubForm);
        delete shrubForm;
    }
    catch (std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

void testBureaucratGradeLimits() {
    std::cout << "\n=== Testing Bureaucrat Grade Limits ===\n" << std::endl;
    
    // Test grade too high
    try {
        Bureaucrat tooHigh("TooHigh", 0);
    }
    catch (std::exception& e) {
        std::cout << "Expected error caught: " << e.what() << std::endl;
    }
    
    // Test grade too low
    try {
        Bureaucrat tooLow("TooLow", 151);
    }
    catch (std::exception& e) {
        std::cout << "Expected error caught: " << e.what() << std::endl;
    }
    
    // Test increment/decrement
    Bureaucrat b1("B1", 2);
    std::cout << b1 << std::endl;
    b1.incrementGrade();
    std::cout << "After increment: " << b1 << std::endl;
    
    try {
        b1.incrementGrade();
    }
    catch (std::exception& e) {
        std::cout << "Expected error caught: " << e.what() << std::endl;
    }
    
    Bureaucrat b2("B2", 149);
    std::cout << b2 << std::endl;
    b2.decrementGrade();
    std::cout << "After decrement: " << b2 << std::endl;
    
    try {
        b2.decrementGrade();
    }
    catch (std::exception& e) {
        std::cout << "Expected error caught: " << e.what() << std::endl;
    }
}

int main() {
    testInternFormCreation();
    testFormExecution();
    testBureaucratGradeLimits();
    
    return 0;
}