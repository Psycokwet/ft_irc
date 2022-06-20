#include "ParsedRequest.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ParsedRequest::ParsedRequest() : _parsed_datas(std::map<std::string, std::string>()),
								 _key(""),
								 _value_buffer(NULL),
								 _parsing_validity_state(PARSE_NOT_ENOUGH_DATAS)
{
}

ParsedRequest::ParsedRequest(const ParsedRequest &src) : _parsed_datas(src._parsed_datas), _key(src._key),
														 _value_buffer(src._value_buffer),
														 _parsing_validity_state(src._parsing_validity_state)
{
	(void)src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ParsedRequest::~ParsedRequest()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ParsedRequest &ParsedRequest::operator=(ParsedRequest const &rhs)
{
	(void)rhs;
	return *this;
}

std::ostream &ParsedRequest::print_request(std::ostream &o) const
{
	return print_cont(o, _parsed_datas, "]\n", "[", ": ");
}

std::ostream &ParsedRequest::print(std::ostream &o) const
{
	o << "Current state :" << GetString(_parsing_validity_state) << std::endl;
	o << "Current key :" << _key << std::endl;
	o << "Current buffer :" << ((_value_buffer == NULL || _parsing_validity_state >= PARSE_FAILURE) ? "NULL" : *_value_buffer) << std::endl;
	o << "Base request :" << std::endl;
	return print_cont(o, _parsed_datas, "]\n", "[", ": ");
}

std::ostream &operator<<(std::ostream &o, ParsedRequest const &i)
{
	one_file_logger(&i, streamFunctionToString(&ParsedRequest::print, &i));
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

ParsedRequest *ParsedRequest::end_build(std::string raw, e_parsing_states endStatus)
{
	(void)raw;
	(void)endStatus;
	return this;
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void ParsedRequest::add_value_parsedDatas(std::string value)
{
	if (this->_parsed_datas.find(this->_key) != this->_parsed_datas.end())
		throw KeyAlreadyUsed();
	if (_key == "")
		throw KeyNotDeclared();
	this->_parsed_datas[_key] = value;
	this->_key = "";
	this->_value_buffer = NULL;
}

void ParsedRequest::add_key_parsedDatas(std::string key)
{
	if (this->_value_buffer != NULL)
		throw ValueBufferAlreadyDeclared();
	if (_key != "")
		throw KeyAlreadyDeclared();
	this->_key = key;
}

std::string ParsedRequest::get_key_parsedDatas() const
{
	if (_key == "")
		throw KeyNotDeclared();
	return this->_key;
}

std::string *ParsedRequest::get_value_buffer_parsedDatas() const
{
	return _value_buffer;
}
void ParsedRequest::set_value_buffer_parsedDatas(std::string *value_buffer)
{
	if (this->_value_buffer != NULL)
		throw ValueBufferAlreadyDeclared();
	this->_value_buffer = value_buffer;
}

void ParsedRequest::set_parsing_validity_state(e_parsing_states parsing_validity_state)
{
	this->_parsing_validity_state = parsing_validity_state;
}

e_parsing_states ParsedRequest::get_parsing_validity_state() const
{
	return this->_parsing_validity_state;
}

/* ************************************************************************** */