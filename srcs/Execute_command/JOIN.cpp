#include "../network/MasterServer.hpp"
/*
** ---------------------------------- USER ----------------------------------
**
**    The JOIN command is used by a user to request to start listening to
**    the specific channel.  Servers MUST be able to parse arguments in the
**    form of a list of target, but SHOULD NOT use lists when sending JOIN
**    messages to clients.
**
**    Once a user has joined a channel, he receives information about
**    all commands his server receives affecting the channel.  This
**    includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.
**    This allows channel members to keep track of the other channel
**    members, as well as channel modes.
**
**    If a JOIN is successful, the user receives a JOIN message as
**    confirmation and is then sent the channel's topic (using RPL_TOPIC) and
**    the list of users who are on the channel (using RPL_NAMREPLY), which
**    MUST include the user joining.
**
**    Note that this message accepts a special argument ("0"), which is
**    a special request to leave all channels the user is currently a member
**    of.  The server will process this message as if the user had sent
**    a PART command (See Section 3.2.2) for each channel he is a member
**    of.
**
**    Numeric Replies:
**
**            ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
**            ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
**            ERR_CHANNELISFULL               ERR_BADCHANMASK
**            ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
**            ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
**            RPL_TOPIC
*/

bool MasterServer::execJOIN(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{

	(void)base;
	(void)parsed_command;
	(void)respQueue;
	Client *client = parsed_command.first; // should not be null regarding how we got here

	if (client->_userOnHost != "")
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_ALREADYREGISTRED, this, client, &base), respQueue);
		return true;
	}
	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
	lazyParsedSubType message(((*(parsed_command.second))[MESSAGE]));
	if (!params.size() || !message.size())
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NEEDMOREPARAMS, this, client, &base), respQueue);
		return true;
	}
	std::string realName = message.front();
	std::string userName = params.front();
	client->_userOnHost = userName;
	client->_realName = realName;
	// mode stuff to do see later
	client->validatedRegistration(respQueue, this);

	return true;
}
