#pragma once

#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <iterator>

void	PmergeMe(char **argv);

template <typename T>
void	MergeSort(T& array, const int& left, const int& right);

template <typename T>
void	insertion(T& min, T& max, const int& last);

template <typename T>
void	FordJohnson(T& array);

class	Error : public std::exception
{
	const char	*what(void) const throw() { return "Error"; }
};