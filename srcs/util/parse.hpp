#ifndef PARSE_HPP
#define PARSE_HPP
#include <cstring>
#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <fstream>
#include "print.hpp"
#include "containerTo.hpp"
void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s);
int isReallyBlank(int c);

#define PREPARE_AND_SKIP_EMPTY_LIGNES(str)                       \
	std::replace_if(str.begin(), str.end(), isReallyBlank, ' '); \
	trim(str);                                                   \
	if (str == "" || str[0] == ';')                              \
		continue;
typedef std::list<std::string> lazyParsedSubType;
typedef std::map<std::string, lazyParsedSubType> lazyParsedType;
lazyParsedType *LazyRequestParser(std::string input);
std::ostream &print_lazyrequest(std::ostream &o, lazyParsedType &container);
#endif