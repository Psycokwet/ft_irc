#include "../IrcServer/IRCServer.hpp"

/*
** ---------------------------------- PASS ----------------------------------
**   Ckeck password users
*/

bool IRCServer::execPASS(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	std::string response;
	int fd = parsed_command.first;
	User *user = _users[fd]; // should not be null regarding hgow we got here
	if (user->_passOK)
	{
		pushToQueue(fd, ": You may not reregister", respQueue);
		// already registered
		std::cout << "1\n";
		return false;
	}

	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));

	switch (params.size())
	{
	case 0:
		pushToQueue(fd, ": Not enough parameters", respQueue); // ERR_NEEDMOREPARAMS 461
		break;
	case 1:
		if (params.front() == _serverPassword)
		{
			user->_passOK = true;
			return true;
		}
		else
			pushToQueue(fd, ": Password incorrect", respQueue); // ERR_PASSWDMISMATCH 464
		break;

	default:
		pushToQueue(fd, TOO_MANY_ARGS, respQueue);
		// too much params
		break;
	}
	return false;
}
