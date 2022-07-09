#include "../../includes/ft_irc.hpp"

std::string	getCodeWithZero(unsigned int n, int width)
{
    std::stringstream res;
    res << std::setw(width) << std::setfill('0') << n; 
	return res.str();
}