#include "BitcoinExchange.hpp"

static bool	separators(std::string& line)
{
	int hasPipe = 0;
	int spaces = 0;
	int tirets = 0;
	for (size_t i = 0 ; line[i] ; i++)
	{
		if (line[i] == '|' && i != 11)
		{
			throw Error("Error: bad input 1 => " + line);
			return false;
		}
		else if (line[i] == '|' && i == 11)
			hasPipe++;
		if (line[i] == ' ' && i != 10 && i != 12)
		{
			throw Error("Error: bad input 2 => " + line);
			return false;
		}
		else if (line[i] == ' ' && (i == 10 || i == 12))
			spaces++;
		if (line[i] == '-' && i != 4 && i != 7)
		{
			throw Error("Error: bad input 3 => " + line);
			return false;
		}
		else if (line[i] == '-' && (i == 4 || i == 7))
			tirets++;
	}
	if (hasPipe != 1 || spaces != 2 || tirets != 2)
	{
		throw Error("Error: bad input 12 => " + line);
		return false;
	}
	return true;
}

static bool	goodDate(std::string& line)
{
	std::string year = line;
	year[4] = '\0';
	if (std::atoi(year.c_str()) < 2009)
	{
		throw Error("Error: bad input => 4 " + line);
		return false;
	}
	std::string month = &line[5];
	month[2] = '\0';
	if (std::atoi(month.c_str()) < 1 || std::atoi(month.c_str()) > 12)
	{
		throw Error("Error: bad input => 5 " + line);
		return false;
	}
	std::string day = &line[8];
	day[2] = '\n';
	if (std::atoi(month.c_str()) == 2)
	{
		if (std::atoi(year.c_str()) % 4 == 0)
		{
			if (std::atoi(day.c_str()) < 1 || std::atoi(day.c_str()) > 29)
			{
				throw Error("Error: bad input 6 => " + line);
				return false;
			}
		}
		else
		{
			if (std::atoi(day.c_str()) < 1 || std::atoi(day.c_str()) > 28)
			{
				throw Error("Error: bad input 7 => " + line);
				return false;
			}
		}
	}
	if (std::atoi(month.c_str()) == 1 || std::atoi(month.c_str()) == 3 || std::atoi(month.c_str()) == 5 || std::atoi(month.c_str()) == 7 || std::atoi(month.c_str()) == 8 || std::atoi(month.c_str()) == 10 || std::atoi(month.c_str()) == 12)
	{
		if (std::atoi(day.c_str()) < 1 || std::atoi(day.c_str()) > 31)
		{
			throw Error("Error: bad input => 8 " + line);
			return false;
		}
	}
	else
	{
		if (std::atoi(day.c_str()) < 1 || std::atoi(day.c_str()) > 30)
		{
			throw Error("Error: bad input => 9 " + line);
			return false;
		}
	}
	return true;
}

static bool	goodChar(std::string& line)
{
	for (size_t i = 0 ; line[i] ; i++)
	{
		if (!std::isdigit(line[i]) && line[i] != ' ' && line[i] != '|' && line[i] != '\n' && line[i] != '-')
		{
			throw Error("Error: bad input => 10 " + line);
			return false;
		}
	}
	return true;
}

void	parsing(std::string& line)
{
	if (line.size() < 14)
	{
		throw Error("Error : bad input => 11 " + line);
		return;
	}
	if (!goodChar(line))
		return;
	if (!separators(line))
		return;
	if (!goodDate(line))
		return;
	if (std::atol(&line[11]) < 0)
		throw Error("Error : not a positive number");
	if (std::atol(&line[11]) > 2147483647)
		throw Error("Error : too large number");
}