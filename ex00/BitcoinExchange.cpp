#include "BitcoinExchange.hpp"

static size_t	date_format(std::string& date)
{
	size_t result = 0;
	for (size_t i = 0 ; i < 10 ; i++)
	{
		if (std::isdigit(date[i]))
			result = result * 10 + (date[i] - '0');
	}
	return result;
}

static std::map<size_t, float>	getDbValues(std::ifstream& db)
{
	std::map<size_t, float> dbValues;
	char buffer[BUFFER_SIZE];
	int i = 0;
	std::string tmp;
	while (db.getline(buffer, BUFFER_SIZE))
	{
		if (i >= 1)
		{
			buffer[10] = '\0';
			tmp = buffer;
			dbValues[date_format(tmp)] = std::atol(&buffer[11]);
		}
		i++;
	}
	db.close();
	return dbValues;
}

void	BitcoinExchange(std::ifstream& db, std::ifstream& fd)
{
	std::map<size_t, float> dbValues = getDbValues(db);
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
				parsing(tmp);
			}
			catch (const std::exception& e) { std::cout << e.what() << "\n"; }
		}
		else
		{
			if (buffer != std::string("date | value"))
			{
				std::cout << "Error : file should begin with 'date | value'\n";
				fd.close();
				exit(1);
			}
		}
		i++;
	}
}

Error::Error(std::string error) : _error(error) {}

Error::~Error(void) throw() {}

const char	*Error::what(void) const throw() { return _error.c_str(); }