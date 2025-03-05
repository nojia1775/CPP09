#include "PmergeMe.hpp"

template <typename T>
static void	fill(T& array, char **argv)
{
	for (size_t i = 0 ; argv[i] ; i++)
	{
		for (size_t j = 0 ; argv[i][j] ; j++)
			if (!isdigit(argv[i][j]))
				throw Error();
		int tmp = std::atoi(argv[i]);
		if (tmp < 0 || tmp > 2147483647)
			throw Error();
		array.push_back(tmp);
	}
}

template <typename T>
void	fusion(T& array, const int& left, const int& middle, const int& right)
{
	size_t a = middle - left + 1;
	size_t b = right - middle;
	T l(a), r(b);

	T::iterator itArr = array.begin() + left;
	T::iterator itL = l.begin();
	for (size_t i = 0 ; i < a ; i++)
		*(itL++) = *(itArr++);
	T::iterator itR = r.begin();
	itArr = array.begin() + middle + 1;
	for (size_t i = 0 ; i < b ; i++)
		*(itR++) = *(itArr++);
	size_t i = 0;
	size_t j = 0;
	size_t k = left;
	itL = l.begin();
	itR = r.begin();
	itArr = array.begin();
	while (i < a && j < b)
	{
		if (*(itL + i) <= *(itR + j))
			*(itArr + k++) = *(itL + i++);
		else
			*(itArr + k++) = *(itR + j++);
	}
	while (i < a)
		*(itArr + k++) = *(itL + i++);
	while (j < b)
		*(itArr + k++) = *(itR + j++);
}

template <typename T>
static void	MergeSort(T& array, const int& left, const int& right)
{
	if (left < right)
	{
		int middle = left + (right - left) / 2;
		MergeSort(array, left, middle);
		MergeSort(array, middle, right);
		fusion(array, left, middle, right);
	}
}

// template <typename T>
// static void	FordJohnson(T& array)
// {
// 	T<int> max;
// 	T<int> min;
// 	int last = -1;
// 	T<int> result;
// 	for (T::iterator it = array.begin() ; it != array.end() ; ++it)
// 	{
// 		if ((it + 1) != array.end())
// 		{
// 			max.push_back(std::max(*it, *(it + 1)));
// 			min.push_back(std::min(*it, *(it + 1)));
// 		}
// 		else
// 			last = *it;
// 	}
// 	return result;
// }

void	PmergeMe(char **argv)
{
	std::vector<int> vector;
	std::list<int> list;
	fill(vector, argv + 1);
	fill(list, argv + 1);
	MergeSort(vector, 0, vector.size() - 1);
	for (std::vector<int>::iterator it = vector.begin() ; it != vector.end() ; ++it)
		std::cout << *it << "\n";
}