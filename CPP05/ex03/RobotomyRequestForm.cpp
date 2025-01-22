#include "RobotomyRequestForm.h"
#include <ctime>

/*** Constructor ***/
RobotomyRequestForm::RobotomyRequestForm( const std::string& target )
	: AForm("RobotomyRequestForm", 72, 45), _target(target) {}

/*** Copy constructor ***/
RobotomyRequestForm::RobotomyRequestForm ( const RobotomyRequestForm& other )
	: AForm(other), _target(other._target) {}

/*** Assignment operator ***/
RobotomyRequestForm& RobotomyRequestForm::operator=( const RobotomyRequestForm& other )
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

/*** Destructor ***/
RobotomyRequestForm::~RobotomyRequestForm() {}

/*** public methods ***/
/*
**	1) check if the form is signed
**	2) check if the bureaucrat has the grade to execute the form
**	if one of those condition isn't matched, an error message is thrown
*/
void	RobotomyRequestForm::execute( const Bureaucrat& executor ) const
{
	this->checkIfSigned();
	this->checkExecution(executor);

	std::cout << "Bzzzz... drilling noises..." << std::endl;

	if (std::rand() % 2 == 0)
		std::cout << _target << " has been robotomized successfully!" << std::endl;
	else
		 std::cout << "Robotomy failed on " << _target << "." << std::endl;
}
