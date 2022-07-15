#include "../network/MasterServer.hpp"

/*
** ---------------------------------- PART ----------------------------------
Command: PART
   Parameters: <channel> *( "," <channel> ) [ <Part Message> ]

   The PART command causes the user sending the message to be removed
   from the list of active members for all given channels listed in the
   parameter string.  If a "Part Message" is given, this will be sent
   instead of the default message, the nickname.  This request is always
   granted by the server.

   Servers MUST be able to parse arguments in the form of a list of
   target, but SHOULD NOT use lists when sending PART messages to
   clients.

   Numeric Replies:

		   ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
		   ERR_NOTONCHANNEL

   Examples:

   PART #twilight_zone             ; Command to leave channel
								   "#twilight_zone"

   PART #oz-ops,&group5            ; Command to leave both channels
								   "&group5" and "#oz-ops".

   :WiZ!jto@tolsun.oulu.fi PART #playzone :I lost
								   ; User WiZ leaving channel
								   "#playzone" with the message "I
								   lost".


*/

bool MasterServer::execPART(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)base;
	(void)parsed_command;
	(void)respQueue;
	Client *client = parsed_command.first;

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
		{
			pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOSUCHCHANNEL, this, client), respQueue);
			continue;
		}
		if (chan->quit_part(respQueue, this, client, base) == false)
		{
			pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOTONCHANNEL, this, client), respQueue);
			continue;
		}
	}
	return (true);
}
