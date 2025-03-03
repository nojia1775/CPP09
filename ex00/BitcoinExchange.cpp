#include "BitcoinExchange.hpp"

static std::map<std::string, float>	getDbValues(std::ifstream& db)
{
	std::map<std::string, float> dbValues;
	char buffer[BUFFER_SIZE];
	int i = 0;
	std::string tmp;
	while (db.getline(buffer, BUFFER_SIZE))
	{
		if (i >= 1)
		{
			buffer[10] = '\0';
			tmp = buffer;
			dbValues[tmp] = std::atof(&buffer[11]);
		}
		i++;
	}
	db.close();
	return dbValues;
}

void	BitcoinExchange(std::ifstream& db, std::ifstream& fd)
{
	std::map<std::string, float> dbValues = getDbValues(db);
	size_t i = 0;
	char buffer[BUFFER_SIZE] = {0};
	std::string tmp;
	while (fd.getline(buffer, BUFFER_SIZE))
	{
		if (i >= 1)
		{
			try
			{
				tmp = buffer;
				float result = parsing(tmp);
				std::map<std::string, float>::iterator bitcoin = dbValues.upper_bound(tmp);
				bitcoin--;
				tmp[10] = '\0';
				std::cout << tmp.c_str() << " => " << result  << " = " << bitcoin->second * result << "\n";
			}
			catch (const std::exception& e) { std::cout << e.what() << "\n"; }
		}
		else
		{
			if (buffer != std::string("date | value"))
			{
				std::cout << "Error: file should begin with 'date | value'\n";
				fd.close();
				exit(1);
			}
		}
		i++;
	}
	if (i == 0)	
		std::cout << "Error: file is empty\n";
	fd.close();
}

Error::Error(std::string error) : _error(error) {}

Error::~Error(void) throw() {}

const char	*Error::what(void) const throw() { return _error.c_str(); }