#include "Channel.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel(std::string name) : _name(name)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Channel::~Channel()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/

std::string Channel::clientListToString()
{
	std::string acc = "";
	std::string sep = "";
	int flags = _MOD_NO_FLAGS;
	for (t_client_modes::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		flags = (*it).second.second;
		if (HAS_TYPE(flags, _MOD_FLAG_ADMIN))
			acc += "@";
		acc += sep + (*it).second.first->getNick();
		sep = " ";
	}
	return acc;
}
void Channel::sendToWholeChannel(std::vector<t_clientCmd> &respQueue, MasterServer *serv, std::string message, Client *exclude)
{
	for (t_client_modes::const_iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (exclude && *exclude == *(it->second.first))
			continue;
		serv->pushToQueue(it->second.first->getFd(), message, respQueue);
	}
}

void Channel::join(std::vector<t_clientCmd> &respQueue, MasterServer *serv, Client *client)
{
	if (_clients.find(client->getFd()) != _clients.end())
		return;
	if (_clients.size())
		_clients[client->getFd()] = std::make_pair(client, _MOD_FLAG_ADMIN);
	else
		_clients[client->getFd()] = std::make_pair(client, _MOD_NO_FLAGS);

	serv->pushToQueue(client->getFd(), CodeBuilder::errorToString(RPL_NAMREPLY, serv, client, NULL, this), respQueue);
}
void Channel::quit(std::vector<t_clientCmd> &respQueue, MasterServer *serv, Client *client)
{
	if (_clients.find(client->getFd()) == _clients.end())
		return;
	_clients.erase(client->getFd());
	(void)respQueue;
	(void)serv;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string Channel::getName()
{
	return "#" + _name;
}
std::string Channel::getTopic()
{
	return _topic;
}
/* ************************************************************************** */