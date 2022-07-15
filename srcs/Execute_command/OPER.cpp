#include "../network/MasterServer.hpp"
/*
** ---------------------------------- OPER----------------------------------
**
**    Command: OPER
**    Parameters: <name> <password>
**
**    A normal user uses the OPER command to obtain operator privileges.
**    The combination of <name> and <password> are REQUIRED to gain
**    Operator privileges.  Upon success, the user will receive a MODE
**    message (see section 3.1.5) indicating the new user modes.
**
**    Numeric Replies:
**
**            ERR_NEEDMOREPARAMS              RPL_YOUREOPER
**            ERR_NOOPERHOST                  ERR_PASSWDMISMATCH
**
**    Example:
**
**    OPER foo bar                    ; Attempt to register as an operator
**                                    using a username of "foo" and "bar"
**                                    as the password.
**/

#ifndef OPER_PWD
#define OPER_PWD ""
#endif
#ifndef OPER_USER
#define OPER_USER ""
#endif

bool MasterServer::execOPER(std::string base, t_client_ParsedCmd &parsed_command)
{
	(void)base;
	(void)parsed_command;
	Client *client = parsed_command.first; // should not be null regarding how we got here
	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
	if (params.size() < 2)
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NEEDMOREPARAMS, this, client, &base));
		return true;
	}
	std::string username = params.front();
	params.pop_front();
	std::string password = params.front();
	params.pop_front();
	std::cout << username << ":" << OPER_USER << ":" << password << ":" << OPER_PWD << "\n";
	if (username == OPER_USER && password == OPER_PWD)
	{
		client->addMode(_MOD_FLAG_OPERATOR);
		pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_YOUREOPER, this, client, &base));
		return true;
	}
	pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_PASSWDMISMATCH, this, client, &base));

	return true;
}
