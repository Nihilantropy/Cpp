#include "ShrubberyCreationForm.h"

/*** Constructor ***/
ShrubberyCreationForm::ShrubberyCreationForm( const std::string& target )
	: AForm("ShrubberyCreationForm", 145, 137), _target(target) {}

/*** Copy constructor ***/
ShrubberyCreationForm::ShrubberyCreationForm ( const ShrubberyCreationForm& other )
	: AForm(other), _target(other._target) {}

/*** Assignment operator ***/
ShrubberyCreationForm& ShrubberyCreationForm::operator=( const ShrubberyCreationForm& other )
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

/*** Destructor ***/
ShrubberyCreationForm::~ShrubberyCreationForm() {}

/*** public method execute ***/
/*
**	1) check if the form is signed
**	2) check if the bureaucrat has the grade to execute the form
**	If one of those condition isn't matched, an error message is thrown.
**	Try to open an outfile and write an ASCII tree on it
*/
void	ShrubberyCreationForm::execute( const Bureaucrat& executor ) const
{
	this->checkIfSigned();
	this->checkExecution(executor);
	
	std::ofstream	outfile((_target + "_shrubbery").c_str());
	if (!outfile.is_open())
		throw FileOpeningException();

	outfile << "     ccee88oo\n"
			<< "  C8O8O8Q8PoOb o8oo\n"
			<< " dOB69QO8PdUOpugoO9bD\n"
			<< "CgggbU8OU qOp qOdoUOdcb\n"
			<< "    6OuU  /p u gcoUodpP\n"
			<< "      \\\\//  /douUP\n"
			<< "        \\\\////\n"
			<< "         |||/\\\n"
			<< "         |||\\/ \n"
			<< "         |||||  \n"
			<< "   .....//||||\\....\n";
	outfile.close();
	std::cout << "Shrubbery created in " << _target + "_shrubbery" << std::endl;
}