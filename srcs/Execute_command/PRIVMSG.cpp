#include "../network/MasterServer.hpp"

/*
** ---------------------------------- PRIVMSG ----------------------------------
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
**	          RPL_AWAY
**
**	 Examples:
**
**	    :Angel!wings@irc.org PRIVMSG Wiz :Are you receiving this message ?
**	                                    ; Message from Angel to Wiz.
**
**	    PRIVMSG Angel :yes I'm receiving it !
**	                                    ; Command to send a message to Angel.
**
**	    PRIVMSG jto@tolsun.oulu.fi :Hello !
**	                                    ; Command to send a message to a user
**	                                    on server tolsun.oulu.fi with
**	                                    username of "jto".
**
**	    PRIVMSG kalt%millennium.stealth.net@irc.stealth.net :Are you a frog?
**	                                    ; Message to a user on server
**	                                    irc.stealth.net with username of
**	                                    "kalt", and connected from the host
**	                                    millennium.stealth.net.
**
**	    PRIVMSG kalt%millennium.stealth.net :Do you like cheese?
**	                                    ; Message to a user on the local
**	                                    server with username of "kalt", and
**	                                    connected from the host
**	                                    millennium.stealth.net.
**
**	    PRIVMSG Wiz!jto@tolsun.oulu.fi :Hello !
**	                                    ; Message to the user with nickname
**	                                    Wiz who is connected from the host
**	                                    tolsun.oulu.fi and has the username
**	                                    "jto".
**
**	    PRIVMSG $*.fi :Server tolsun.oulu.fi rebooting.
**	                                    ; Message to everyone on a server
**	                                    which has a name matching *.fi.
**
**	    PRIVMSG #*.edu :NSFNet is undergoing work, expect interruptions
**	                                    ; Message to all users who come from
**	                                    a host which has a name matching
**	                                    *.edu.
**
**
**		Note: Send to one user, one channel, multiple channels at once
**/

bool MasterServer::execPRIVMSG(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)base;
	(void)parsed_command;
	(void)respQueue;
	Client *client = parsed_command.first; // should not be null regarding how we got here
	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
	lazyParsedSubType channel(((*(parsed_command.second))[CHANNELS]));
	if (!params.size() && !channel.size())
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NORECIPIENT, this, client, &base), respQueue);
		return true;
	}
	lazyParsedSubType message(((*(parsed_command.second))[MESSAGE]));
	if (!message.size())
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOTEXTTOSEND, this, client, &base), respQueue);
		return true;
	}

	// Do this as in excecMODE
	// if (channel.size())
	// {
	// 	std::string destChannelName = channel.front();
	// 	Channel *destChannel = this->findChanneWithName(destChannelName);
	// 	if (!destChannel)
	// 	{
	// 		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_CANNOTSENDTOCHAN, this, client, &destChannel), respQueue);
	// 		return true;
	// 	}
	// 	pushToQueue(client->_fd, ": response for Channel privmsg", respQueue);

	// }
	// else if (params.size())
	// {
	// 	std::string destNick = params.front();
	// 	Client *destClient = this->findClientWithNick(destNick);
	// 	if (!destClient)
	// 	{
	// 		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOSUCHNICK, this, client, &destNick), respQueue);
	// 		return true;
	// 	}
	// 	pushToQueue(destClient->_fd, ":" + getFullClientID(client) + " " + base, respQueue);
	// }
	return true;
}
