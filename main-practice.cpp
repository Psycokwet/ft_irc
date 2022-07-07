// Return a string rep of n zero-padded whose final length is width
#include <string>
#include <iostream>
#include <iomanip> // setw, setfill

#define RPL_WELCOME				001 

static std::string	toStrZeroPadded(unsigned int n, int width)
{
    std::stringstream res;
    res << std::setw(width) << std::setfill('0') << n; 
	return res.str();
}

int main(void)
{
    std::string res = toStrZeroPadded(RPL_WELCOME, 3);
    std::cout << RPL_WELCOME << std::endl;
    std::cout << "|" << res << "|\n";
    return (0);
}