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
void	changeIterator(T& it, const int& index) { std::advance(it, index); }

template <typename T>
void	fusion(T& array, const int& left, const int& middle, const int& right)
{
	int a = middle - left + 1;
	int b = right - middle;
	T l(a), r(b);

	typename T::iterator itArr = array.begin();
	std::advance(itArr, left);
	typename T::iterator itL = l.begin();
	for (int i = 0 ; i < a ; i++)
		*(itL++) = *(itArr++);
	typename T::iterator itR = r.begin();
	itArr = array.begin();
	std::advance(itArr, 1 + middle);
	for (int i = 0 ; i < b ; i++)
		*(itR++) = *(itArr++);
	int i = 0;
	int j = 0;
	int k = left;
	itL = l.begin();
	itR = r.begin();
	itArr = array.begin();
	while (i < a && j < b)
	{
		changeIterator(itL, i);
		changeIterator(itR, j);
		if (*itL <= *itR)
		{
			changeIterator(itL, -i);
			changeIterator(itR, -j);
			changeIterator(itArr, k);
			changeIterator(itL, i);
			*itArr = *itL;
			changeIterator(itArr, -k);
			changeIterator(itL, -i);
			k++;
			i++;
		}
		else
		{
			changeIterator(itL, -i);
			changeIterator(itR, -j);
			changeIterator(itArr, k);
			changeIterator(itR, j);
			*itArr = *itR;
			changeIterator(itArr, -k);
			changeIterator(itR, -j);
			k++;
			j++;
		}
	}
	while (i < a)
	{
		changeIterator(itArr, k);
		changeIterator(itL, i);
		*itArr = *itL;
		changeIterator(itArr, -k);
		changeIterator(itL, -i);
		i++;
		k++;
	}
	while (j < b)
	{
		changeIterator(itArr, k);
		changeIterator(itR, j);
		*itArr = *itR;
		changeIterator(itArr, -k);
		changeIterator(itR, -j);
		k++;
		j++;
	}
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
void	insertion(T& min, T& max, const int& last)
{
	typename T::iterator minIt = min.begin();
	for ( ; minIt != min.end() ; ++minIt)
	{
		typename T::iterator maxIt = max.begin();
		for ( ; maxIt != max.end() ; ++maxIt)
		{
			if (*minIt < *maxIt)
			{
				max.insert(maxIt, *minIt);
				break;
			}
		}
	}
	if (last >= 0)
	{
		typename T::iterator it = max.begin();
		for ( ; it != max.end() ; ++it)
		{
			if (last < *it)
			{
				max.insert(it, last);
				return;
			}
		}
		typename T::iterator endIt = max.end();
		std::advance(endIt, -1);
		max.insert(endIt, last);
	}
}

template <typename T>
void	FordJohnson(T& array)
{
	T max;
	T min;
	int last = -1;
	T result;
	typename T::iterator it = array.begin();
	for ( ; it != array.end() ; ++it)
	{
		if (++it != array.end())
		{
			--it;
			max.push_back(std::max(*it, *(++it)));
			--it;
			min.push_back(std::min(*it, *(++it)));
			--it;
		}
		else
			last = *(--it);
	}
	MergeSort(max, 0, max.size() - 1);
	insertion(min, max, last);
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
	std::cout << "STD::VECTOR :\n";
	std::vector<int>::const_iterator vectorIt = vector.begin();
	for ( ; vectorIt != vector.end() ; ++vectorIt)
		std::cout << *vectorIt << "\n";
	std::cout << "\nSTD::LIST: \n";
	std::list<int>::const_iterator listIt = list.begin();
	for ( ; listIt != list.end() ; ++listIt)
		std::cout << *listIt << "\n";
}