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

	typename T::iterator itArr = array.begin() + left;
	typename T::iterator itL = l.begin();
	for (size_t i = 0 ; i < a ; i++)
		*(itL++) = *(itArr++);
	typename T::iterator itR = r.begin();
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
void	MergeSort(T& array, const int& left, const int& right)
{
	if (left < right)
	{
		int middle = left + (right - left) / 2;
		MergeSort(array, left, middle);
		MergeSort(array, middle + 1, right);
		fusion(array, left, middle, right);
	}
}

template <typename T>
void	insertion(T& min, T& max)
{
	for (typename T::iterator minIt = min.begin() ; minIt != min.end() ; ++minIt)
	{
		for (typename T::iterator maxIt = max.begin() ; maxIt != max.end() : ++maxIt)
		{
			if (*minIt < *maxIt)
			{
				max.insert(maxIt, *minIt);
				break;
			}
		}
	}
}

template <typename T>
void	FordJohnson(T& array)
{
	T max;
	T min;
	int last = -1;
	T result;
	for (typename T::iterator it = array.begin() ; it != array.end() ; ++it)
	{
		if ((it + 1) != array.end())
		{
			max.push_back(std::max(*it, *(it + 1)));
			min.push_back(std::min(*it, *(it + 1)));
		}
		else
			last = *it;
	}
	MergeSort(max, 0, max.size() - 1);
	insertion(min, max);
	array = max;
}

void	PmergeMe(char **argv)
{
	std::vector<int> vector;
	std::list<int> list;
	fill(vector, argv + 1);
	fill(list, argv + 1);
	FordJohnson(vector);
	FordJohnson(list);
	for (std::vector<int>::const_iterator it = vector.begin() ; it != vector.end() ; ++it)
		std::cout << *it << "\n";
	for (std::list<int>::const_iterator it = list.begin() ; it != list.end() ; ++it)
		std::cout << *it << "\n";
}