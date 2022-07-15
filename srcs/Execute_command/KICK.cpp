#include "../network/MasterServer.hpp"

/*
** ---------------------------------- KICK ----------------------------------
**      Command: KICK
**    Parameters: <channel> *( "," <channel> ) <user> *( "," <user> )
**                [<comment>]
**
**    The KICK command can be used to request the forced removal of a user
**    from a channel.  It causes the <user> to PART from the <channel> by
**    force.  For the message to be syntactically correct, there MUST be
**    either one channel parameter and multiple user parameter, or as many
**    channel parameters as there are user parameters.  If a "comment" is
**    given, this will be sent instead of the default message, the nickname
**    of the user issuing the KICK.
**
**    The server MUST NOT send KICK messages with multiple channels or
**    users to clients.  This is necessarily to maintain backward
**    compatibility with old client software.
**
**    Numeric Replies:
**
**            ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
**            ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
**            ERR_USERNOTINCHANNEL            ERR_NOTONCHANNEL
**
**    Examples:
**
**    KICK &Melbourne Matthew         ; Command to kick Matthew from
**                                    &Melbourne
**
**    KICK #Finnish John :Speaking English
**                                    ; Command to kick John from #Finnish
**                                    using "Speaking English" as the
**                                    reason (comment).
**
**    :WiZ!jto@tolsun.oulu.fi KICK #Finnish John
**                                    ; KICK message on channel #Finnish
**                                    from WiZ to remove John from channel
*/

bool MasterServer::execKICK(std::string base, t_client_ParsedCmd &parsed_command)
{
	(void)base;
	(void)parsed_command;
	Client *client = parsed_command.first;

	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
	lazyParsedSubType channels(((*(parsed_command.second))[CHANNELS]));
	lazyParsedSubType message(((*(parsed_command.second))[MESSAGE]));
	std::string notification = "Good riddance !";
	if (message.size())
		notification = message.front();
	if (!params.size() || !channels.size() || (channels.size() != params.size() && channels.size() > 1))
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NEEDMOREPARAMS, this, client, &base));
		return true;
	}
	if (channels.size() > 1)
	{
		while (channels.size())
		{
			Channel *chan = findChanneWithName(channels.front());
			channels.pop_front();
			if (!chan)
			{
				pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOSUCHCHANNEL, this, client, &base));
				return true;
			}
			if (!chan->kick(params.front(), client, notification))
				return true;
		}
	}
	else
	{
		Channel *chan = findChanneWithName(*it);
		if (!chan)
		{
			pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOSUCHCHANNEL, this, client, &base));
			return true;
		}
		chan->kick(params.front(), client, notification);
	}
	return true;
}
