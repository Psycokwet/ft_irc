#include "../network/MasterServer.hpp"

/*
** ---------------------------------- VERSION ----------------------------------
**  Command: VERSION
   Parameters: [ <target> ]

   The VERSION command is used to query the version of the server
   program.  An optional parameter <target> is used to query the version
   of the server program which a client is not directly connected to.

   Wildcards are allowed in the <target> parameter.

   Numeric Replies:

		   ERR_NOSUCHSERVER                RPL_VERSION

   Examples:

   VERSION tolsun.oulu.fi          ; Command to check the version of
								   server "tolsun.oulu.fi".

**/
bool MasterServer::execVERSION(std::string base, t_client_ParsedCmd &parsed_command)
{
	(void)base;
	(void)parsed_command;
	Client *client = parsed_command.first; // should not be null regarding how we got here

	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
	// if (params.front() == getHost())
	// pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_VERSION, this, client, &base));
	pushToQueue(client->_fd, ":" + getFullClientID(client) + " NOTICE " + client->getUserOnHost() + ": " + getServerName() + " :" + getServerVersion() + END_OF_COMMAND);
	// else
	// 	pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOSUCHSERVER, this, client, &base));
	return true;
}
