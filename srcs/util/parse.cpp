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

std::ostream &print_lazyrequest(std::ostream &o, lazyParsedType &container)
{
	for (typename lazyParsedType::const_iterator it = container.begin(); it != container.end(); it++)
	{
		o << it->first << ": [\n";
		print_cont(o, it->second) << "]\n";
	}
	return o;
}
lazyParsedType *LazyRequestParser(std::string input)
{
	std::string tmp_block;
	if (input.rfind("\r\n") != input.size() - 2)
		return NULL;
	std::stringstream ss(input);
	lazyParsedType *parsedDatas = new lazyParsedType();

	std::list<std::string> cut = stringToList(input, ' ');
	if (cut.size() > 1)
	{
		(*parsedDatas)["method"] = lazyParsedSubType();
		(*parsedDatas)["method"].push_back(cut.front());
		cut.pop_front();
		return parsedDatas;
	}
	print_lazyrequest(std::cout, *parsedDatas);
	return parsedDatas;
}