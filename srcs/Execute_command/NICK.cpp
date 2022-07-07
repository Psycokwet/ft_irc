#include "../IrcServer/IRCServer.hpp"

/*
** ---------------------------------- NICK ----------------------------------
User can change/set their nickname by: /nick new_nickname
Hanle Errors:
- If user puts /nick without params, Hexchat won't send anything to server.
- If user puts /nick with serveral params, Hexchat sends only the first param to server.
- Nickname used by other user.
- Nickname has invalid characters.

*/

// ! How to get/update User and Channel's info in here
// ! How to get numeric replies. (includes/code.hpp)

bool IRCServer::execNICK(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)base;
	(void)parsed_command;
	(void)respQueue;
	// std::string response;
	// Client *client = parsed_command.first; // should not be null regarding hgow we got here
	// if (client->_passOK)
	// {
	// 	pushToQueue(user->getFd(), ": You may not reregister", respQueue);
	// 	// already registered
	// 	std::cout << "1\n";
	// 	return false;
	// }

	// lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));

	// switch (params.size())
	// {
	// case 0:
	// 	pushToQueue(client->getFd(), ": Not enough parameters", respQueue); // ERR_NEEDMOREPARAMS 461
	// 	break;
	// case 1:
	// 	if (params.front() == _serverPassword)
	// 	{
	// 		client->_passOK = true;
	// 		return true;
	// 	}
	// 	else
	// 		pushToQueue(client->getFd(), ": Password incorrect", respQueue); // ERR_PASSWDMISMATCH 464
	// 	break;

	// default:
	// 	pushToQueue(client->getFd(), TOO_MANY_ARGS, respQueue);
	// 	// too much params
	// 	break;
	// }
	/*std::string		response;

	if ( ((*(parsed_command.second))[PARAMS]).empty() ) // Hexchat won't send it but have this condition just in case.
	{
		response = ":No nickname given";
		pushToQueue(parsed_command.first, response, respQueue);
		return true;
	}*/

	return true;
}