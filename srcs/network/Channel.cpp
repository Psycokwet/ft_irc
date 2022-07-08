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

void Channel::sendToWholeChannel(std::vector<t_clientCmd> &respQueue, MasterServer *serv, std::string message, Client *exclude)
{
	for (std::list<Client *>::const_iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (exclude && *exclude == **it)
			continue;
		serv->pushToQueue((*it)->getFd(), message, respQueue);
	}
}

void join(std::vector<t_clientCmd> &respQueue, MasterServer *serv, Client *client)
{
	(void)respQueue;
	(void)serv;
	(void)client;
}
void quit(std::vector<t_clientCmd> &respQueue, MasterServer *serv, Client *client)
{
	(void)respQueue;
	(void)serv;
	(void)client;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */