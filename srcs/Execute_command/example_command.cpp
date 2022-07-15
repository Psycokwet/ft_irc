#include "../network/MasterServer.hpp"

bool MasterServer::example_command(std::string base, t_client_ParsedCmd &parsed_command)
{
	(void)base;
	(void)parsed_command;
	std::cout << "I am an example command, i'm here to show you how it work, but I should never be called in prod. I have been called with "
			  << ((*(parsed_command.second))[COMMAND]).front() << std::endl;
	return false;
}