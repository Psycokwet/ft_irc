#include "parse.hpp"
void ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(isblank))));
}

void rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(isblank))).base(), s.end());
}

void trim(std::string &s)
{
	ltrim(s);
	rtrim(s);
}

int isReallyBlank(int c)
{
	if (isblank(c) || c == '\r')
		return true;
	return false;
}

std::map<std::string, std::list<std::string> > *LazyRequestParser(std::string input)
{
	std::string tmp_block;
	if (input.rfind("\r\n") != input.size() - 2)
		return NULL;
	std::stringstream ss(input);
	std::map<std::string, std::list<std::string> > *parsedDatas = new std::map<std::string, std::list<std::string> >();
	while (std::getline(ss, tmp_block, ' '))
	{
		std::cout << "hello " << tmp_block << std::endl;
	}

	return parsedDatas;
}