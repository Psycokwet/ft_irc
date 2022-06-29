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

bool IRCServer::execNICK(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	// (void)respQueue;

	// std::cout << "I am exec"
	// 		  << ((*(parsed_command.second))[COMMAND]).front() << std::endl;
	// std::cout << "PARAMS = " << ((*(parsed_command.second))[PARAMS]).front() << std::endl;

	std::string		response;

	if ( ((*(parsed_command.second))[PARAMS]).empty() ) // Hexchat won't send it but have this condition just in case.
	{
		response = ":No nickname given";
		pushToQueue(parsed_command.first, response, respQueue);
		return true;
	}

	return true;
}