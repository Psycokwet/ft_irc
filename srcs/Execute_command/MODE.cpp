#include "../network/MasterServer.hpp"
/*
** ---------------------------------- MODE USER OR CHANNEL ----------------------------------
**
** User mode message
**
** 	  Command: MODE
**    Parameters: <nickname>
** 			   *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )
**
**    The user MODE's are typically changes which affect either how the
**    client is seen by others or what 'extra' messages the client is sent.
**
**    A user MODE command MUST only be accepted if both the sender of the
**    message and the nickname given as a parameter are both the same.  If
**    no other parameter is given, then the server will return the current
**    settings for the nick.
**
** 	  The available modes are as follows:
**
** 		   a - user is flagged as away;
** 		   i - marks a users as invisible;
** 		   w - user receives wallops;
** 		   r - restricted user connection;
** 		   o - operator flag;
** 		   O - local operator flag;
** 		   s - marks a user for receipt of server notices.
**
**   Additional modes may be available later on.
**
**
**
**    The flag 'a' SHALL NOT be toggled by the user using the MODE command,
**    instead use of the AWAY command is REQUIRED.
**
**    If a user attempts to make themselves an operator using the "+o" or
**    "+O" flag, the attempt SHOULD be ignored as users could bypass the
**    authentication mechanisms of the OPER command.  There is no
**    restriction, however, on anyone `deopping' themselves (using "-o" or
**    "-O").
**
**    On the other hand, if a user attempts to make themselves unrestricted
**    using the "-r" flag, the attempt SHOULD be ignored.  There is no
**    restriction, however, on anyone `deopping' themselves (using "+r").
**    This flag is typically set by the server upon connection for
**    administrative reasons.  While the restrictions imposed are left up
**    to the implementation, it is typical that a restricted user not be
**    allowed to change nicknames, nor make use of the channel operator
**    status on channels.
**
**    The flag 's' is obsolete but MAY still be used.
**
**    Numeric Replies:
**
** 		   ERR_NEEDMOREPARAMS   ok           ERR_USERSDONTMATCH ok
** 		   ERR_UMODEUNKNOWNFLAG  ok          RPL_UMODEIS somehow should not use it
**
**/
/*
**
**  Channel mode message
**
**       Command: MODE
**    Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )
**
**    The MODE command is provided so that users may query and change the
**    characteristics of a channel.  For more details on available modes
**    and their uses, see "Internet Relay Chat: Channel Management" [IRC-
**    CHAN].  Note that there is a maximum limit of three (3) changes per
**    command for modes that take a parameter.
**
**    Numeric Replies:
**
**            ERR_NEEDMOREPARAMS              ERR_KEYSET
**            ERR_NOCHANMODES                 ERR_CHANOPRIVSNEEDED
**            ERR_USERNOTINCHANNEL            ERR_UNKNOWNMODE
**            RPL_CHANNELMODEIS
**            RPL_BANLIST                     RPL_ENDOFBANLIST
**            RPL_EXCEPTLIST                  RPL_ENDOFEXCEPTLIST
**            RPL_INVITELIST                  RPL_ENDOFINVITELIST
**            RPL_UNIQOPIS
**/

bool MasterServer::execMODE_CLIENT(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)base;
	(void)parsed_command;
	(void)respQueue;
	Client *client = parsed_command.first; // should not be null regarding how we got here
	(void)client;
	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
	if (params.size() < 2)
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NEEDMOREPARAMS, this, client), respQueue);
		return true;
	}
	std::string nick = params.front();
	params.pop_front();
	std::string target_modes = params.front();
	params.pop_front();
	if (nick != client->getNick())
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_USERSDONTMATCH, this, client), respQueue);
		return true;
	}

	bool add = true;
	if (target_modes.at(0) == '-' || target_modes.at(0) == '+')
	{
		if (target_modes.at(0) == '-')
			add = false;
		target_modes = target_modes.substr(1);
	}
	e_mode_client modes;
	try
	{
		modes = Client::stringToClientSettableMode(target_modes);
	}
	catch (const Client::unknownModeException &e)
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_UMODEUNKNOWNFLAG, this, client), respQueue);
		return true;
	}
	// catch (const Client::doubleSetModeException &e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }
	bool success = false;
	if (add)
		success = client->addMode(modes);
	else
		success = client->minusMode(modes);

	if (success)
		pushToQueue(client->_fd, ":" + getFullClientID(client) + " MODE " + client->getNick() + " :" + (add ? "+" : "-") + Client::modeToString(modes) + END_OF_COMMAND, respQueue);

	return true;
}
bool MasterServer::execMODE_CHANNEL(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)base;
	(void)parsed_command;
	(void)respQueue;
	Client *client = parsed_command.first; // should not be null regarding how we got here
	(void)client;
	lazyParsedSubType channels(((*(parsed_command.second))[CHANNELS]));
	for (lazyParsedSubType::iterator it = channels.begin(); it != channels.end(); it++)
	{
		Channel *chan = findChanneWithName(*it);
		if (!chan)
		{
			// no chan
			return true;
		}

		pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_CHANNELMODEIS, this, client, NULL, chan), respQueue);
		// join one after the other
	}

	return true;
}
bool MasterServer::execMODE(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	lazyParsedSubType channels(((*(parsed_command.second))[CHANNELS]));
	if (!channels.size())
	{
		return execMODE_CLIENT(base, parsed_command, respQueue);
	}
	return execMODE_CHANNEL(base, parsed_command, respQueue);
}
