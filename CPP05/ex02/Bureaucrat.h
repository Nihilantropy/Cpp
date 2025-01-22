#ifndef BUREAUCRAT_H
#define BUREAUCRAT_H

# include <iostream>
# include <string>
# include <stdexcept>
# include "AForm.h"

class AForm;

class Bureaucrat
{
public:
	/*** constructor ***/
	Bureaucrat( const std::string& name, int grade );
	/*** copy constructor ***/
	Bureaucrat( const Bureaucrat& other );
	/*** assignment operator ***/
	Bureaucrat& operator=( const Bureaucrat& other );
	/*** destructor ***/
	~Bureaucrat();

	/*** getter ***/
	const std::string&	getName( void ) const;
	int					getGrade( void ) const;

	/*** public methods ***/
	void				incrementGrade();
	void				decrementGrade();
	void				signForm( AForm& form ) const;
	void				executeForm( const AForm& form ) const;

	/*** exception class with what() method override ***/
	class	GradeTooHighException : public std::exception
	{
	public:
		/*** public methods ***/
		const char*	what() const throw()
		{
			return "Grade too high!";
		}
	};

	class	GradeTooLowException : public std::exception
	{
	public:
		const char*	what() const throw()
		{
			return "Grade too low!";
		}
	};

private:
	const std::string	_name;
	int					_grade;
	void				checkGrade( int grade ) const ;
};

std::ostream& operator<<( std::ostream& os, const Bureaucrat& bureaucrat );

#endif
