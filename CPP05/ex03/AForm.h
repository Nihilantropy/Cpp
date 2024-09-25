#ifndef AForm_H
#define AForm_H

# include <iostream>
# include <string>
# include <stdexcept>
# include <fstream>
# include "Bureaucrat.h"
# include "RobotomyRequestForm.h"
# include "ShrubberyCreationForm.h"
# include "PresidentialPardonForm.h"

class Bureaucrat;

class Form
{
public:
	/*** constructor ***/
	Form( const std::string& name, const int gradeToSign, const int grade_toExec );
	/*** copy constructor ***/
	Form( const Form& other );
	/*** assignment operator ***/
	Form& operator=( const Form& other );
	/*** destructor ***/
	virtual ~Form();

	/*** getters ***/
	const std::string&	getName() const;
	bool				getIfSigned() const;
	int					getGradeToSign() const;
	int					getGradeToExec() const;

	/*** public methods ***/
	void				beSigned( const Bureaucrat& bureaucrat );
	void				checkIfSigned( void ) const;
	void				checkExecution( const Bureaucrat& executor ) const;

	/*** pure virutal method ***/
	virtual void		execute( const Bureaucrat& executor ) const = 0;

	/*** exception class with what() method override ***/
	class GradeTooHighException : public std::exception
	{
	public:
		/*** public methods ***/
		const char*	what() const throw()
		{
			return "grade is too high!";
		}
	};

	class GradeTooLowException : public std::exception
	{
	public:
		/*** public methods ***/
		const char*	what() const throw()
		{
			return "grade is too low!";
		}
	};

	class FormNotSignedException : public std::exception
	{
	public:
		/*** public methods ***/
		const char*	what() const throw()
		{
			return "Form is not signed!";
		}
	};

private:
	const std::string	_name;
	bool				_isSigned;
	const int			_gradeToSign;
	const int			_gradeToExec;

	void				checkGrade( int grade ) const ;
};

std::ostream& operator<<( std::ostream& os, const Form& form );

#endif