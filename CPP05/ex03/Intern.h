#ifndef INTERN_H
#define INTERN_H

# include "AForm.h"
# include "RobotomyRequestForm.h"
# include "ShrubberyCreationForm.h"
# include "PresidentialPardonForm.h"
# include <utility>

class Intern
{
public:
	/*** constructor ***/
	Intern();
	/*** copy constructor ***/
	Intern( const Intern& other );
	/*** assignment operator ***/
	Intern& operator=( const Intern& other );
	/*** destructor ***/
	~Intern();

	/*** public methods ***/
	AForm*	makeForm( const std::string& name, const std::string& target );

	class FormNameException : public std::exception
	{
	public:
		/*** public methods ***/
		const char*	what() const throw()
		{
			return "Form name provided is incorrect.";
		}
	};
private:
	/*** private methods ***/
	/* function for form creation */
	AForm* createRobotomyRequest(const std::string& target) const;
	AForm* createShrubberyCreation(const std::string& target) const;
	AForm* createPresidentialPardon(const std::string& target) const;

	/* array of pointers to member functions */
	typedef AForm* (Intern::*FormCreator)(const std::string&) const;
	/* pairing the form name with the corrisponding 'createForm' function */
	struct FormMapping
	{
		const char* _name;
		FormCreator _creator;
	};

	static const FormMapping	formMappings[3];
};

#endif
