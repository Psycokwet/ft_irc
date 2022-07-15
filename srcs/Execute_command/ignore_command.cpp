#include "../network/MasterServer.hpp"

bool MasterServer::ignore_command(std::string base, t_client_ParsedCmd &parsed_command)
{
	(void)base;
	(void)parsed_command;
	return true;
}
