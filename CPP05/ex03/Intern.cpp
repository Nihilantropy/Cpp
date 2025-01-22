#include "Intern.h"

/***  constructor ***/
Intern::Intern() {}

/***  Copy constructor ***/
Intern::Intern( const Intern& other ) { *this = other; }

/***  assignment operator override ***/
Intern& Intern::operator=( const Intern& other )
{
	(void)other;
	return *this;
}

/***  Destructor ***/
Intern::~Intern() {}

/*** public methods ***/
/* array of pointers to member functions */
AForm* Intern::makeForm(const std::string& name, const std::string& target)
{
	for (size_t i = 0; i < 3; ++i)
	{
		if (name == formMappings[i]._name)
			return (this->*(formMappings[i]._creator))(target);
	}
	throw FormNameException();
}

/*** private methods ***/
/*	
**	form mapping implementation 
**	to pair the name of the form with
**	the corrisponding 'createForm' function
*/
const	Intern::FormMapping Intern::formMappings[3] = {
	{"robotomy request", &Intern::createRobotomyRequest},
	{"shrubbery creation", &Intern::createShrubberyCreation},
	{"presidential pardon", &Intern::createPresidentialPardon}
};

/* function for form creation */
AForm*	Intern::createRobotomyRequest(const std::string& target) const {
		return new RobotomyRequestForm(target);
}

AForm*	Intern::createShrubberyCreation(const std::string& target) const {
		return new ShrubberyCreationForm(target);
}

AForm*	Intern::createPresidentialPardon(const std::string& target) const {
		return new PresidentialPardonForm(target);
}
