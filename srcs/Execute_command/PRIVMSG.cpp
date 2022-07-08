#include "../IrcServer/IRCServer.hpp"

/*
** ---------------------------------- NICK ----------------------------------
** Parameters: <msgtarget> <text to be sent>
**
**    PRIVMSG is used to send private messages between users, as well as to
**    send messages to channels.  <msgtarget> is usually the nickname of
**    the recipient of the message, or a channel name.
**
**    The <msgtarget> parameter may also be a host mask (#<mask>) or server
**    mask ($<mask>).  In both cases the server will only send the PRIVMSG
**    to those who have a server or host matching the mask.  The mask MUST
**    have at least 1 (one) "." in it and no wildcards following the last
**    ".".  This requirement exists to prevent people sending messages to
**    "#*" or "$*", which would broadcast to all users.  Wildcards are the
**    '*' and '?'  characters.  This extension to the PRIVMSG command is
**    only available to operators.
**
**    Numeric Replies:
**
**            ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
**            ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
**            ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
**            ERR_NOSUCHNICK
**            RPL_AWAY
**/

bool IRCServer::execPRIVMSG(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)base;
	(void)parsed_command;
	(void)respQueue;
	Client *client = parsed_command.first; // should not be null regarding how we got here
	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
	if (!params.size())
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NORECIPIENT, this, client, &base), respQueue);
		return true;
	}
	lazyParsedSubType message(((*(parsed_command.second))[MESSAGE]));
	if (!params.size())
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOTEXTTOSEND, this, client, &base), respQueue);
		return true;
	}
	std::string destNick = params.front();
	Client *destClient = this->findClientWithNick(destNick);
	if (!destClient)
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOSUCHNICK, this, client, &destNick), respQueue);
		return true;
	}
	pushToQueue(destClient->_fd, base, respQueue);

	// more to do
	return true;
}