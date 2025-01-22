#include "AForm.h"

/*** constructor ***/
AForm::AForm( const std::string& name, const int gradeToSign, const int gradeToExec)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExec(gradeToExec)
{
	checkGrade(gradeToSign);
	checkGrade(gradeToExec);
}

/*** copy constructor ***/
AForm::AForm( const AForm& other )
	: _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExec(other._gradeToExec) {}

/*** assignment operator ***/
AForm&	AForm::operator=( const AForm& other )
{
	if (this != &other )
	{
		_isSigned = other._isSigned;
	}
	return *this;
}

/*** destructor ***/
AForm::~AForm() {}

/*** getters ***/
const std::string&	AForm::getName() const { return _name; }
bool				AForm::getIfSigned() const { return _isSigned; }
int					AForm::getGradeToSign() const { return _gradeToSign; }
int					AForm::getGradeToExec() const { return _gradeToExec; }

/*** public methods ***/
void	AForm::beSigned( const Bureaucrat& bureaucrat )
{
	if (bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	_isSigned = true;
}

void	AForm::checkIfSigned( void ) const
{
	if (this->getIfSigned() == false)
		throw FormNotSignedException();
}

void	AForm::checkExecution( const Bureaucrat& executor ) const
{
	if (executor.getGrade() > this->getGradeToExec())
		throw GradeTooLowException();
}

/*** private methods ***/
void	AForm::checkGrade( int grade ) const
{
	if (grade < 1)
		throw GradeTooHighException();
	if (grade > 150)
		throw GradeTooLowException();
}

/*** '<<' operator overload ***/
std::ostream& operator<<( std::ostream& os, const AForm& form )
{
	os << "Form " << form.getName() << ", signed: " << (form.getIfSigned() ? "yes" : "no")
	   << ", grade required to sign: " << form.getGradeToSign()
	   << ", grade required to execute: " << form.getGradeToExec();
	return os;
}
