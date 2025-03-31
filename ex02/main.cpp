#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	if (argc <= 2)
	{
		std::cerr << "Error\n";
		return 1;
	}
	try
	{
		PmergeMe(argc, argv);
	}
	catch (const std::exception& e) { std::cout << e.what() << "\n"; return 1; }
	return 0;
}