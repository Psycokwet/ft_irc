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
**		Note: Here we implement: Send msg from one user to other user, to same channel, to another channel (by commandn line).
**				Cannot send to multiple channels.
*/
bool MasterServer::execPRIVMSG(std::string base, t_client_ParsedCmd &parsed_command)
{
	(void)base;
	(void)parsed_command;
	lazyParsedSubType command(((*(parsed_command.second))[COMMAND]));

	bool silentError = command.front() == "NOTICE";
	Client *client = parsed_command.first; // should not be null regarding how we got here

	lazyParsedSubType channels(((*(parsed_command.second))[CHANNELS]));
	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
	if (!params.size() && !channels.size())
	{
		if (!silentError)
			pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NORECIPIENT, this, client, &base));
		return true;
	}

	lazyParsedSubType message(((*(parsed_command.second))[MESSAGE]));
	if (!message.size())
	{
		if (!silentError)
			pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOTEXTTOSEND, this, client, &base));
		return true;
	}
	if (message.size() && message.front() == "VERSION")
	{
		return execVERSION(base, parsed_command); // No error possible, no need on silentError
	}

	if (!channels.size())
	{
		return execPRIVMSG_CLIENT(base, parsed_command, silentError);
	}
	return execPRIVMSG_CHANNEL(base, parsed_command, silentError);
}

bool MasterServer::execPRIVMSG_CHANNEL(std::string base, t_client_ParsedCmd &parsed_command, bool silentError)
{
	(void)base;

	Client *client = parsed_command.first; // should not be null regarding how we got here
	lazyParsedSubType channels(((*(parsed_command.second))[CHANNELS]));
	std::string destChannelName = channels.front();
	Channel *destChannel = this->findChanneWithName(destChannelName);
	if (!destChannel)
	{
		if (!silentError)

			pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOSUCHNICK, this, client, &destChannelName));
		return true;
	}
	destChannel->sendToWholeChannel(this, ":" + getFullClientID(client) + " " + base + END_OF_COMMAND, client);
	return true;
}

bool MasterServer::execPRIVMSG_CLIENT(std::string base, t_client_ParsedCmd &parsed_command, bool silentError)
{
	Client *client = parsed_command.first; // should not be null regarding how we got here
	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
	std::string destNick = params.front();
	Client *destClient = this->findClientWithNick(destNick);
	if (!destClient)
	{
		if (!silentError)
			pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOSUCHNICK, this, client, &destNick));
		return true;
	}
	pushToQueue(destClient->_fd, ":" + getFullClientID(client) + " " + base + END_OF_COMMAND);
	return true;
}
