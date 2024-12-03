#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Date.hpp"
#include "err.hpp"

std::map<Date, float>	loadDatabase(void);
void					printDatabase(const std::map<Date, float>& database);

#endif