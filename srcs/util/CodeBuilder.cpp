#include "CodeBuilder.hpp"

/*
** ------------------------------- STATIC --------------------------------
*/
t_code_dictionary CodeBuilder::initCodeDictionnary()
{
	t_code_dictionary map;
	map[RPL_WELCOME] = &CodeBuilder::toStringRPL_WELCOME;
	map[ERR_NEEDMOREPARAMS] = &CodeBuilder::toStringNEEDMOREPARAMS;
	return map;
}

t_code_dictionary CodeBuilder::_codeDictionnary = CodeBuilder::initCodeDictionnary();

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

std::ostream &operator<<(std::ostream &o, CodeBuilder const &i)
{
	(void)i;
	// o << "Value = " << i.getValue();
	return o;
}

/*
** --------------------------------- STATIC METHODS ----------------------------------
*/

std::string CodeBuilder::errorToString(int err, IRCServer *server, Client *client, std::string *s)
{
	if (_codeDictionnary.find(err) != _codeDictionnary.end())
		return errorCodeToString(err) + " " + _codeDictionnary[err](s, server, client);
	return "042 :No registered error code found";
}
std::string CodeBuilder::errorCodeToString(int err)
{
	std::stringstream ss;
	ss << std::setw(3) << std::setfill('0') << err;
	return ss.str();
}

std::string CodeBuilder::toStringRPL_WELCOME(std::string *s, IRCServer *server, Client *client)
{
	(void)s;
	return "Welcome to the Internet Relay Network" + client->getNick() + "!" + client->getNick() + "@" + server->getHost();
}

std::string CodeBuilder::toStringNEEDMOREPARAMS(std::string *command_name, IRCServer *server, Client *client)
{
	(void)server;
	(void)client;
	return (*command_name) + ":Not enough parameters";
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */