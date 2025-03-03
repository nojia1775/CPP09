#include "BitcoinExchange.hpp"

static bool	separators(std::string& line)
{
	int hasPipe = 0;
	int spaces = 0;
	int tirets = 0;
	int dots = 0;
	for (size_t i = 0 ; line[i] ; i++)
	{
		if (line[i] == '|' && i != 11)
		{
			throw Error("Error: bad input => " + line);
			return false;
		}
		else if (line[i] == '|' && i == 11)
			hasPipe++;
		if (line[i] == ' ' && i != 10 && i != 12)
		{
			throw Error("Error: bad input => " + line);
			return false;
		}
		else if (line[i] == ' ' && (i == 10 || i == 12))
			spaces++;
		if (line[i] == '-' && i != 4 && i != 7)
		{
			throw Error("Error: bad input => " + line);
			return false;
		}
		else if (line[i] == '-' && (i == 4 || i == 7))
			tirets++;
		if (line[i] == '.' && i < 14)
		{
			throw Error("Error: bad input => " + line);
			return false;
		}
		else if (line[i] == '.' && i >= 14)
			dots++;
	}
	if (hasPipe != 1 || spaces != 2 || tirets != 2 || dots > 1)
	{
		throw Error("Error: bad input => " + line);
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
		throw Error("Error: bad input => " + line);
		return false;
	}
	std::string month = &line[5];
	month[2] = '\0';
	if (std::atoi(month.c_str()) < 1 || std::atoi(month.c_str()) > 12)
	{
		throw Error("Error: bad input => " + line);
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
				throw Error("Error: bad input => " + line);
				return false;
			}
		}
		else
		{
			if (std::atoi(day.c_str()) < 1 || std::atoi(day.c_str()) > 28)
			{
				throw Error("Error: bad input => " + line);
				return false;
			}
		}
	}
	if (std::atoi(month.c_str()) == 1 || std::atoi(month.c_str()) == 3 || std::atoi(month.c_str()) == 5 || std::atoi(month.c_str()) == 7 || std::atoi(month.c_str()) == 8 || std::atoi(month.c_str()) == 10 || std::atoi(month.c_str()) == 12)
	{
		if (std::atoi(day.c_str()) < 1 || std::atoi(day.c_str()) > 31)
		{
			throw Error("Error: bad input => " + line);
			return false;
		}
	}
	else
	{
		if (std::atoi(day.c_str()) < 1 || std::atoi(day.c_str()) > 30)
		{
			throw Error("Error: bad input => " + line);
			return false;
		}
	}
	return true;
}

static bool	goodChar(std::string& line)
{
	for (size_t i = 0 ; line[i] ; i++)
	{
		if (!std::isdigit(line[i]) && line[i] != ' ' && line[i] != '|' && line[i] != '\n' && line[i] != '-' && line[i] != '.')
		{
			throw Error("Error: bad input => " + line);
			return false;
		}
	}
	return true;
}

float	parsing(std::string& line)
{
	if (line.size() < 14)
	{
		throw Error("Error: bad input => " + line);
		return -1;
	}
	if (!goodChar(line))
		return -1;
	if (!separators(line))
		return -1;
	if (!goodDate(line))
		return -1;
	if (std::atof(&line[13]) < 0)
		throw Error("Error: not a positive number");
	if (std::atof(&line[13]) > 2147483647)
		throw Error("Error: too large number");
	return std::atof(&line[13]);
}