#include "../IrcServer/IRCServer.hpp"

/*
** ---------------------------------- PASS ----------------------------------
**   Ckeck password users
*/

bool IRCServer::execPASS(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	std::cout << "HELLO\n";
	std::string response;
	int fd = parsed_command.first;
	User *user = _users[fd];
	if (!user) // ERROR
		return false;
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
		std::cout << "2\n";
		pushToQueue(fd, ": Not enough parameters", respQueue); // ERR_NEEDMOREPARAMS 461
		break;
	case 1:
		std::cout << "6\n";
		if (params.front() == _serverPassword)
		{
			std::cout << "3\n";
			user->_passOK = true;
			return true;
		}
		else
			pushToQueue(fd, ": Password incorrect", respQueue); // ERR_PASSWDMISMATCH 464
		break;

	default:
		std::cout << "5\n";
		pushToQueue(fd, ": Too much params", respQueue);
		// too much params
		break;
	}
	std::cout << "4\n";
	return false;
}
