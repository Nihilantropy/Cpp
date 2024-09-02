#include "../include/FragTrap.h"

FragTrap::FragTrap( std::string name ) : ClapTrap(name)
{
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
	std::cout << "FragTrap constructor called for " << _name << std::endl;
}

FragTrap::~FragTrap() { std::cout << "FragTrap Destructor called!" << std::endl; }

void	FragTrap::highFivesGuys( void )
{
	std::cout << _name << " requests a high five! \"Hey you there! Give me your best high five of your life!\"" << std::endl;
}
