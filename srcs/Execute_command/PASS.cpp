#include "../IrcServer/IRCServer.hpp"

/*
** ---------------------------------- PASS ----------------------------------
**   Ckeck password users
**
** Numeric Replies:
**            ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED
*/
bool IRCServer::execPASS(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)base;
	Client *client = parsed_command.first; // should not be null regarding how we got here
	if (client->_passOK)
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_ALREADYREGISTRED, this, client, &base), respQueue);
		return false;
	}

	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));

	switch (params.size())
	{
	case 0:
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NEEDMOREPARAMS, this, client, &base), respQueue);
		break;
	case 1:
		if (params.front() == _serverPassword)
		{
			client->_passOK = true;
			return true;
		}
		else
			pushToQueue(client->_fd, ": Password incorrect", respQueue); // not necessary regarding doc
		break;

	default:
		pushToQueue(client->_fd, TOO_MANY_ARGS, respQueue); // not necessary regarding doc
		// too much params
		break;
	}
	return false;
}
