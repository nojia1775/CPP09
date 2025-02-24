#include "BitcoinExchange.hpp"

static void	parsing(std::string& line)
{
	if (line.size() < 14)
		throw Error("Error : bad input => " + line);
	if (line[11] != '|')
		throw Error("Error : bad file format");
	if (std::atol(&line[11]) < 0)
		throw Error("Error : not a positive number");
	if (std::atol(&line[11]) > 2147483647)
		throw Error("Error : too large number");
}

static size_t	date_format(std::string& date)
{
	size_t result = 0;
	for (size_t i = 0 ; i < 10 ; i++)
	{
		if (std::isdigit(date[i]))
			result = result * 10 + std::atoi(&date[i]);
	}
	return result;
}

void	BitcoinExchange(std::ifstream& db, std::ifstream& fd)
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
	std::map<std::string, float> file;
	i = 0;
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
			if (buffer != std::string("date | value"))
				std::cout << "Error : file should begin with 'date | value'\n";
		i++;
	}
	db.close();
}

Error::Error(std::string error) : _error(error) {}

Error::~Error(void) throw() {}

const char	*Error::what(void) const throw() { return _error.c_str(); }