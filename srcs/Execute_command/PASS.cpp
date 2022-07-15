#include "../network/MasterServer.hpp"

/*
** ---------------------------------- PASS ----------------------------------
**   Ckeck password users
**
** Numeric Replies:
**            ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED
*/
bool MasterServer::execPASS(std::string base, t_client_ParsedCmd &parsed_command)
{
	(void)base;
	Client *client = parsed_command.first; // should not be null regarding how we got here
	if (client->_passOK)
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_ALREADYREGISTRED, this, client, &base));
		return false;
	}

	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));

	switch (params.size())
	{
	case 0:
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NEEDMOREPARAMS, this, client, &base));
		break;
	case 1:
		if (params.front() == _password)
		{
			client->_passOK = true;
			return true;
		}
		else
			pushToQueue(client->_fd, std::string(": Password incorrect") + END_OF_COMMAND); // not necessary regarding doc
		break;

	default:
		pushToQueue(client->_fd, std::string(TOO_MANY_ARGS) + END_OF_COMMAND); // not necessary regarding doc
		// too much params
		break;
	}
	return false;
}
