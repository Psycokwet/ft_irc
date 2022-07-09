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
** 		   ERR_NEEDMOREPARAMS              ERR_USERSDONTMATCH
** 		   ERR_UMODEUNKNOWNFLAG            RPL_UMODEIS
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

bool MasterServer::execMODE(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)base;
	(void)parsed_command;
	(void)respQueue;
	Client *client = parsed_command.first; // should not be null regarding how we got here

	lazyParsedSubType channels(((*(parsed_command.second))[CHANNELS]));
	if (!channels.size())
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NEEDMOREPARAMS, this, client, &base), respQueue);
		return true;
	}
	for (lazyParsedSubType::iterator it = channels.begin(); it != channels.end(); it++)
	{
		Channel *chan = findChanneWithName(*it);
		if (!chan)
			chan = createChannel(*it);
		if (!chan)
		{
			std::cout << "Something wrong happened with channel, should not happen TAG#58\n";
			return true;
		}
		chan->join(respQueue, this, client, base);
		// join one after the other
	}
	return true;
}
