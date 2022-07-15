#include "../network/MasterServer.hpp"

/*
** ---------------------------------- TIME ----------------------------------
Command: TIME
   Parameters: [ <target> ]

   The time command is used to query local time from the specified
   server. If the <target> parameter is not given, the server receiving
   the command must reply to the query.

   Wildcards are allowed in the <target> parameter.

   Numeric Replies:

		   ERR_NOSUCHSERVER              RPL_TIME

   Examples:
   TIME tolsun.oulu.fi             ; check the time on the server
								   "tolson.oulu.fi"
*/

bool MasterServer::execTIME(std::string base, t_client_ParsedCmd &parsed_command)
{
	(void)base;
	(void)parsed_command;
	Client *client = parsed_command.first;

	pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_TIME, this, client, &base));
	return (true);
}
