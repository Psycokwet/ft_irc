#include "../IrcServer/IRCServer.hpp"

bool IRCServer::ignore_command(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)parsed_command;
	(void)respQueue;
	return true;
}
