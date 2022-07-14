#include "parse.hpp"

bool isNonPrint(char c) { return !isprint(c); }
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
	for (lazyParsedType::const_iterator it = container.begin(); it != container.end(); it++)
	{
		o << it->first << ": [\n";
		print_cont(o, it->second) << "]\n";
	}
	return o;
}

std::string cleanString(std::string s)
{
	s.erase(std::remove_if(s.begin(), s.end(), isNonPrint), s.end());
	return s;
}

std::string cleanBlanks(std::string s)
{
	s.erase(std::remove_if(s.begin(), s.end(), isReallyBlank), s.end());
	return s;
}

lazyParsedType *LazyRequestParser(std::string input)
{
	std::string tmp_block;
	if (input.rfind("\r\n") != input.size() - 2)
		return NULL;
	input = cleanString(input.substr(0, input.size() - 2));
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
		(*parsedDatas)[COMMAND].push_back(cleanBlanks(cut.front()));
		cut.pop_front();
	}
	else
	{
		delete parsedDatas;
		return NULL;
	}
	for (lazyParsedSubType::iterator it = cut.begin(); it != cut.end(); it++)
	{
		if (!it->size() || it->at(0) != '#')
			continue;
		if (parsedDatas->find(CHANNELS) != parsedDatas->end())
		{
			delete parsedDatas;
			return NULL;
		}
		lazyParsedSubType sub = stringToList(cleanBlanks((*it).substr(1)), ",#");
		(*parsedDatas)[CHANNELS] = lazyParsedSubType(sub);
		cut.erase(it);
		break;
	}
	if (cut.size() >= 1)
	{
		lazyParsedSubType tmp_lazy = lazyParsedSubType();
		for (lazyParsedSubType::iterator it = cut.begin(); it != cut.end(); it++)
		{
			std::string tmp_s = cleanBlanks(*it);
			if (!tmp_s.size())
				continue;
			tmp_lazy.push_back(tmp_s);
		}
		if (tmp_lazy.size())
			(*parsedDatas)[PARAMS] = lazyParsedSubType(tmp_lazy);
	}
	return parsedDatas;
}

std::string removeTokenAtEnd(std::string &input, std::string token)
{
	if (input.rfind(token) != input.size() - 2)
		return input;
	return input.substr(0, input.size() - 2);
}
