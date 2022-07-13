#include "../network/MasterServer.hpp"

/*
** ---------------------------------- NICK ----------------------------------
** NICK command is used to give user a nickname or change the existing one.
**
**  Numeric Replies:
**
**           ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME illegal chars in nick
**           ERR_NICKNAMEINUSE               ERR_NICKCOLLISION colision between servers osef
**           ERR_UNAVAILRESOURCE not sure if needed            ERR_RESTRICTED
**/

bool MasterServer::execNICK(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)base;
	(void)parsed_command;
	(void)respQueue;
	Client *client = parsed_command.first; // should not be null regarding how we got here
	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));

	if (!params.size())
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NONICKNAMEGIVEN, this, client, &base), respQueue);
		return true;
	}
	std::string new_nick = params.front();
	if (client->_nick == new_nick)
	{
		client->validatedRegistration(respQueue, this);
		return true;
	}
	if (this->findClientWithNick(new_nick))
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NICKNAMEINUSE, this, client, &new_nick), respQueue);
		return true;
	}
	std::cout << new_nick << " NOT IN USE\n";
	client->_nick = new_nick;
	client->validatedRegistration(respQueue, this);
	return true;
}