#include "../IrcServer/IRCServer.hpp"

bool IRCServer::ignore_command(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)base;
	(void)parsed_command;
	(void)respQueue;
	return true;
}
