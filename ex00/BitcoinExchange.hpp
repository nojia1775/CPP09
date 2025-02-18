#ifndef BITCOINEXCHANGE_HPP

# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <fstream>
# include <string>

std::map<std::string, float>&	BitcoinExchange(const std::ifstream& db, const std::ifstream& file);

#endif