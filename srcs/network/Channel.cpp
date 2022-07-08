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
	for (t_client_modes::iterator it = _clients.begin(); it != _clients.end(); it++)
		delete it->second.second; // only delete modes, NOT CLIENTS, NEVER HERE
	_clients.clear();
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/

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
		_clients[client->getFd()] = std::make_pair(client, new ClientMode(_MOD_FLAG_ADMIN));
	else
		_clients[client->getFd()] = std::make_pair(client, new ClientMode());
	(void)respQueue;
	(void)serv;
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

/* ************************************************************************** */