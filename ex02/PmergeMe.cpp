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
		std::advance(itL, i);
		std::advance(itR, j);
		if (*itL <= *itR)
		{
			std::advance(itL, -i);
			std::advance(itR, -j);
			std::advance(itArr, k);
			std::advance(itL, i);
			*itArr = *itL;
			std::advance(itArr, -k);
			std::advance(itL, -i);
			k++;
			i++;
		}
		else
		{
			std::advance(itL, -i);
			std::advance(itR, -j);
			std::advance(itArr, k);
			std::advance(itR, j);
			*itArr = *itR;
			std::advance(itArr, -k);
			std::advance(itR, -j);
			k++;
			j++;
		}
	}
	while (i < a)
	{
		std::advance(itArr, k);
		std::advance(itL, i);
		*itArr = *itL;
		std::advance(itArr, -k);
		std::advance(itL, -i);
		i++;
		k++;
	}
	while (j < b)
	{
		std::advance(itArr, k);
		std::advance(itR, j);
		*itArr = *itR;
		std::advance(itArr, -k);
		std::advance(itR, -j);
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
		if (maxIt == max.end())
			max.insert(maxIt, *minIt);
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
	while (it != array.end())
	{
		++it;
		if (it != array.end())
		{
			--it;
			max.push_back(std::max(*it, *(++it)));
			--it;
			min.push_back(std::min(*(it++), *it));
			--it;
			std::advance(it, 2);
		}
		else
		{
			last = *(--it);
			break;
		}
	}
	MergeSort(max, 0, max.size() - 1);
	insertion(min, max, last);
	array = max;
}

void	PmergeMe(int argc, char **argv)
{
	std::vector<int> vector;
	std::list<int> list;
	fill(vector, argv + 1);
	fill(list, argv + 1);
	std::cout << "Before (std::vector):\t";
	std::vector<int>::const_iterator Vit = vector.begin();
	for ( ; Vit != vector.end() ; ++Vit)
		std::cout << *Vit << " ";
	std::cout << "\n";
	std::cout << "Before (std::list):\t";
	std::list<int>::const_iterator Lit = list.begin();
	for ( ; Lit != list.end() ; ++Lit)
		std::cout << *Lit << " ";
	std::cout << "\n";
	clock_t startVector = clock();
	FordJohnson(vector);
	clock_t endVector = clock();
	clock_t startList = clock();
	FordJohnson(list);
	clock_t endList = clock();
	std::cout << "After (std::vector):\t";
	Vit = vector.begin();
	for ( ; Vit != vector.end() ; ++Vit)
		std::cout << *Vit << " ";
	std::cout << "\n";
	std::cout << "After (std::list):\t";
	Lit = list.begin();
	for ( ; Lit != list.end() ; ++Lit)
		std::cout << *Lit << " ";
	std::cout << "\n";
	double timeVector = (double)(endVector - startVector) / CLOCKS_PER_SEC * 1000000;
	double timeList = (double)(endList - startList) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector : " << timeVector << " us\n";
	std::cout << "Time to process a range of " << argc - 1 << " elements with std::list : " << timeList << " us\n";
}