#include "../network/MasterServer.hpp"
/*
** ---------------------------------- DIE ----------------------------------
**
**        Command: DIE
**    Parameters: None
**
**    An operator can use the DIE command to shutdown the server.  This
**    message is optional since it may be viewed as a risk to allow
**    arbitrary people to connect to a server as an operator and execute
**    this command.
**
**    The DIE command MUST always be fully processed by the server to which
**    the sending client is connected and MUST NOT be passed onto other
**    connected servers.
**
**    Numeric Replies:
**
**            ERR_NOPRIVILEGES
**
**    Example:
**
**    DIE                             ; no parameters required.
**
**
**/

bool MasterServer::execDIE(std::string base, t_client_ParsedCmd &parsed_command)
{
	(void)base;
	(void)parsed_command;
	Client *client = parsed_command.first; // should not be null regarding how we got here
	if (!HAS_TYPE(client->getMode(), _MOD_FLAG_OPERATOR))
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOPRIVILEGES, this, client));
	exit(0);
	return true;
}
