#include "../IrcServer/IRCServer.hpp"

/*
** ---------------------------------- PASS ----------------------------------
**   Ckeck password users
*/

bool IRCServer::execPASS(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	std::string response;
	Client *client = parsed_command.first; // should not be null regarding hgow we got here
	if (client->_passOK)
	{
		pushToQueue(client->_fd, ": You may not reregister", respQueue); // ERR_ALREADYREGISTERED
		// already registered
		return false;
	}

	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));

	switch (params.size())
	{
	case 0:
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NEEDMOREPARAMS, this, client), respQueue);
		break;
	case 1:
		if (params.front() == _serverPassword)
		{
			client->_passOK = true;
			return true;
		}
		else
			pushToQueue(client->_fd, ": Password incorrect", respQueue);
		break;

	default:
		pushToQueue(client->_fd, TOO_MANY_ARGS, respQueue);
		// too much params
		break;
	}
	return false;
}
