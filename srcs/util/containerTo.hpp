#ifndef CONTAINER_TO_HPP
#define CONTAINER_TO_HPP
#include <cstring>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <iostream>
#include <sstream>

std::list<std::string> stringToList(std::string base, char tokenizer);
std::list<std::string> stringToList(std::string base, char tokenizer, std::string filterOut);
std::list<std::string> stringToList(std::string base, std::string tokenizer);
std::list<std::string> stringToListKeepTokenizer(std::string base, std::string tokenizer);

#endif