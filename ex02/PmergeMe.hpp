#pragma once

#include <iostream>
#include <algorithm>
#include <list>
#include <vector>

void	PmergeMe(char **argv);

class	Error : public std::exception
{
	const char	*what(void) const throw() { return "Error"; }
};