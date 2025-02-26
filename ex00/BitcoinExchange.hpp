#ifndef BITCOINEXCHANGE_HPP

# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <fstream>
# include <string>
# include <cstdlib>

# define BUFFER_SIZE 1024

void	BitcoinExchange(std::ifstream& db, std::ifstream& file);

class	Error : public std::exception
{
	private:
		std::string	_error;

	public:
				Error(std::string error);
				~Error(void) throw();
		const char	*what(void) const throw();
};

A FINIR PSQ T AS EU LA FLEMME DE LE FAIRE AU TAF

#endif