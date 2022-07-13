#include "containerTo.hpp"

std::list<std::string> stringToList(std::string base, char tokenizer)
{
	std::list<std::string> result;
	std::string tmp_block;
	std::stringstream ss(base);
	while (std::getline(ss, tmp_block, tokenizer))
		result.push_back(tmp_block);
	return result;
}

std::list<std::string> stringToList(std::string base, char tokenizer, std::string filterOut)
{
	std::list<std::string> result;
	std::string tmp_block;
	std::stringstream ss(base);
	while (std::getline(ss, tmp_block, tokenizer))
	{
		if (filterOut == tmp_block)
			continue;
		result.push_back(tmp_block);
	}
	return result;
}
std::list<std::string> stringToList(std::string base, std::string tokenizer)
{
	std::list<std::string> result;
	std::string tmp_block;
	int index_end;
	while ((index_end = base.find(tokenizer)) != -1)
	{
		result.push_back(base.substr(0, index_end));
		base = base.substr(index_end + tokenizer.size());
	}
	result.push_back(base.substr(0, index_end));
	return result;
}
std::list<std::string> stringToListKeepTokenizer(std::string base, std::string tokenizer)
{
	std::list<std::string> result;
	std::string tmp_block;
	int index_end;
	while ((index_end = base.find(tokenizer)) != -1)
	{
		result.push_back(base.substr(0, index_end + tokenizer.size()));
		base = base.substr(index_end + tokenizer.size());
	}
	result.push_back(base.substr(0, index_end));
	return result;
}