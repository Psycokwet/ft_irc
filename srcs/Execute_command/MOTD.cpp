#include "../network/MasterServer.hpp"

/*
** ---------------------------------- MOTD ----------------------------------
Command: MOTD
   Parameters: [ <target> ]

   The MOTD command is used to get the "Message Of The Day" of the given
   server, or current server if <target> is omitted.

   Wildcards are allowed in the <target> parameter.

   Numeric Replies:
		   RPL_MOTDSTART                   RPL_MOTD
		   RPL_ENDOFMOTD                   ERR_NOMOTD

*/

bool MasterServer::execMOTD(std::string base, t_client_ParsedCmd &parsed_command)
{
	(void)base;
	(void)parsed_command;
	Client *client = parsed_command.first;

	pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_MOTDSTART, this, client));
	pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_MOTD, this, client));
	pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_ENDOFMOTD, this, client));
	return (true);
}
