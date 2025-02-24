#include "BitcoinExchange.hpp"

std::map<std::string, float>	BitcoinExchange(std::ifstream& db, std::ifstream& file)
{
	(void)file;
	std::map<std::string, float> dbValues;
	char buffer[BUFFER_SIZE];
	size_t i = 0;

	std::string tmp;
	while (db.getline(buffer, BUFFER_SIZE, ','))
	{
		if (i % 2 == 0)
		{
			tmp = buffer;
			dbValues[buffer] = 0;
		}
		else
		{
			dbValues[tmp] = std::atof(buffer);
			std::cout << tmp << " = " << dbValues[tmp] << "\n";
		}
		i++;
	}
	db.close();
	return dbValues;
}