#ifndef BITCOINEXCHANGE_HPP

# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <fstream>
# include <string>
# include <cstdlib>

# define BUFFER_SIZE 1024

std::map<std::string, float>	BitcoinExchange(std::ifstream& db, std::ifstream& file);

#endif