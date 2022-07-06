#include "../IrcServer/IRCServer.hpp"

bool IRCServer::example_command(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)parsed_command;
	(void)respQueue;
	std::cout << "I am an example command, i'm here to show you how it work, but I should never be called in prod. I have been called with "
			  << ((*(parsed_command.second))[COMMAND]).front() << std::endl;
	return false;
}