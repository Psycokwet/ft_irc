#include "../network/MasterServer.hpp"

/*
** ---------------------------------- INVITE ----------------------------------
**    Command: INVITE
**    Parameters: <nickname> <channel>
**
**    The INVITE command is used to invite a user to a channel.  The
**    parameter <nickname> is the nickname of the person to be invited to
**    the target channel <channel>.  There is no requirement that the
**    channel the target user is being invited to must exist or be a valid
**    channel.  However, if the channel exists, only members of the channel
**    are allowed to invite other users.  When the channel has invite-only
**    flag set, only channel operators may issue INVITE command.
**
**    Only the user inviting and the user being invited will receive
**    notification of the invitation.  Other channel members are not
**    notified.  (This is unlike the MODE changes, and is occasionally the
**    source of trouble for users.)
**
**    Numeric Replies:
**
**            ERR_NEEDMOREPARAMS  ok            ERR_NOSUCHNICK
**            ERR_NOTONCHANNEL     ok           ERR_USERONCHANNEL
**            ERR_CHANOPRIVSNEEDED
**            RPL_INVITING                    RPL_AWAY
**
**    Examples:
**
**    :Angel!wings@irc.org INVITE Wiz #Dust
**
**                                    ; Message to WiZ when he has been
**                                    invited by user Angel to channel
**                                    #Dust
**
**    INVITE Wiz #Twilight_Zone       ; Command to invite WiZ to
**                                    #Twilight_zone
*/
bool MasterServer::execINVITE(std::string base, t_client_ParsedCmd &parsed_command)
{
	(void)base;
	(void)parsed_command;
	Client *client = parsed_command.first; // should not be null regarding how we got here

	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
	lazyParsedSubType channels(((*(parsed_command.second))[CHANNELS]));
	if (!params.size() || !channels.size())
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NEEDMOREPARAMS, this, client, &base));
		return true;
	}

	Channel *targetChannel = this->findChanneWithName(channels.front());
	std::cout << "Trying to invite on " << targetChannel->getName() << std::endl;
	if (!targetChannel)
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOSUCHNICK, this, client, &(channels.front())));
		return true;
	}
	std::cout << "Trying to invite user : " << params.front() << std::endl;
	Client *destClient = findClientWithNick(params.front());
	if (!destClient)
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOSUCHNICK, this, client, &(params.front())));
		return true;
	}
	if (!targetChannel->findClientWithNick(client->getNick()))
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOTONCHANNEL, this, client, &base, targetChannel));
		return true;
	}
	if (targetChannel->findClientWithNick(params.front()))
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_USERONCHANNEL, this, client, &params.front(), targetChannel));
		return true;
	}

	if (HAS_TYPE(destClient->getMode(), _MOD_FLAG_AWAY))
		pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_AWAY, this, destClient));
	else
		pushToQueue(destClient->_fd, ":" + getFullClientID(client) + " " + base + END_OF_COMMAND);
	pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_INVITING, this, client, destClient->getNick(), targetChannel));
	return true;
}
