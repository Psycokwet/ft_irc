#include "../IrcServer/IRCServer.hpp"
/*
** ---------------------------------- USER ----------------------------------
**
**    The USER command is used at the beginning of connection to specify
**    the username, hostname and realname of a new user.
**
**    The <mode> parameter should be a numeric, and can be used to
**    automatically set user modes when registering with the server.  This
**    parameter is a bitmask, with only 2 bits having any signification: if
**    the bit 2 is set, the user mode 'w' will be set and if the bit 3 is
**    set, the user mode 'i' will be set.  (See Section 3.1.5 "User
**    Modes").
**
**    The <realname> may contain space characters.
**
**    Numeric Replies:
**
**            ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED
*/

bool IRCServer::execUSER(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{

	(void)base;
	(void)parsed_command;
	(void)respQueue;
	Client *client = parsed_command.first; // should not be null regarding how we got here

	if (client->_userOnHost != "")
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_ALREADYREGISTRED, this, client), respQueue);
		return true;
	}
	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
	lazyParsedSubType message(((*(parsed_command.second))[MESSAGE]));
	if (!params.size() || !message.size())
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NEEDMOREPARAMS, this, client), respQueue);
		return true;
	}
	std::string realName = message.front();
	std::string userName = params.front();
	client->_userOnHost = userName;
	client->_realName = realName;
	// mode stuff to do see later
	pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_WELCOME, this, client), respQueue);
	pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_YOURHOST, this, client), respQueue);
	pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_CREATED, this, client), respQueue);
	pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_MYINFO, this, client), respQueue);

	return true;
}
