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
static T&	FordJohnson(const T& array)
{
	T<int> max;
	T<int> min;
	int last = -1;
	T<int> result;
	for (T::iterator it = array.begin() ; it != array.end() ; ++it)
	{
		if ((it + 1) != array.end())
		{
			max.push_back(std::max(*it, *(it + 1)));
			min.push_back(std::min(*it, *(it + 1)));
		}
		else
			last = *it;
	}
}

void	PmergeMe(char **argv)
{
	std::vector<int> vector;
	std::list<int> list;
	fill(vector, argv + 1);
	fill(list, argv + 1);
}