#include "PresidentialPardonForm.h"

/*** Constructor ***/
PresidentialPardonForm::PresidentialPardonForm( const std::string& target )
	: AForm("PresidentialPardonForm", 25, 5), _target(target) {}

/*** Copy constructor ***/
PresidentialPardonForm::PresidentialPardonForm ( const PresidentialPardonForm& other )
	: AForm(other), _target(other._target) {}

/*** Assignment operator ***/
PresidentialPardonForm& PresidentialPardonForm::operator=( const PresidentialPardonForm& other )
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

/*** Destructor ***/
PresidentialPardonForm::~PresidentialPardonForm() {}

/*** public methods ***/
/*
**	1) check if the form is signed
**	2) check if the bureaucrat has the grade to execute the form
**	if one of those condition isn't matched, an error message is thrown
*/
void	PresidentialPardonForm::execute( const Bureaucrat& executor ) const
{
	this->checkIfSigned();
	this->checkExecution(executor);

	std::cout << _target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}
