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

#define CHANNELS "channels"
#define MESSAGE "message"
#define PARAMS "params"
#define COMMAND "command"
lazyParsedType *LazyRequestParser(std::string input)
{
	std::string tmp_block;
	if (input.rfind("\r\n") != input.size() - 2)
		return NULL;
	input = input.substr(0, input.size() - 2);
	lazyParsedType *parsedDatas = new lazyParsedType();

	int message_index = input.find(':');
	if (message_index != -1)
	{
		(*parsedDatas)[MESSAGE] = lazyParsedSubType();
		(*parsedDatas)[MESSAGE].push_back(input.substr(message_index + 1));
		input = input.substr(0, message_index);
	}

	lazyParsedSubType cut = stringToList(input, ' ');
	if (cut.size() >= 1)
	{
		(*parsedDatas)[COMMAND] = lazyParsedSubType();
		(*parsedDatas)[COMMAND].push_back(cut.front());
		cut.pop_front();
	}
	else
	{
		delete parsedDatas;
		return NULL;
	}
	for (lazyParsedSubType::iterator it = cut.begin(); it != cut.end(); it++)
	{
		if (it->at(0) == '#')
		{
			if (parsedDatas->find(CHANNELS) != parsedDatas->end())
			{
				delete parsedDatas;
				return NULL;
			}
			lazyParsedSubType sub = stringToList((*it).substr(1), ",#");
			(*parsedDatas)[CHANNELS] = lazyParsedSubType(sub);
			cut.erase(it++);
			continue;
		}
	}
	if (cut.size() >= 1)
	{
		(*parsedDatas)[PARAMS] = lazyParsedSubType(cut);
	}
	return parsedDatas;
}