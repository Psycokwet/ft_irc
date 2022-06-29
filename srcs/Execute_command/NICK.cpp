#include "../IrcServer/IRCServer.hpp"

bool IRCServer::execNICK(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)parsed_command;
	(void)respQueue;
	std::cout << "I am execNICK"
			  << ((*(parsed_command.second))[COMMAND]).front() << std::endl;
	return false;
}