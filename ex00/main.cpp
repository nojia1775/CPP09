#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: programme needs a file to open\n";
		return 1;
	}
	std::ifstream db("data.csv");
	if (!db)
	{
		std::cout << "Error: could not open data base\n";
		return 1;
	}
	std::ifstream file(argv[1]);
	if (!file)
	{
		std::cout << "Error: could not open file\n";
		return 1;
	}
	BitcoinExchange(db, file);
	return 0;
}