#include "../network/MasterServer.hpp"
/*
** ---------------------------------- WHO ----------------------------------
**
**    Command: WHO
**    Parameters: [ <mask> [ "o" ] ]
**
**    The WHO command is used by a client to generate a query which returns
**    a list of information which 'matches' the <mask> parameter given by
**    the client.  In the absence of the <mask> parameter, all visible
**    (users who aren't invisible (user mode +i) and who don't have a
**    common channel with the requesting client) are listed.  The same
**    result can be achieved by using a <mask> of "0" or any wildcard which
**    will end up matching every visible user.
**
**    The <mask> passed to WHO is matched against users' host, server, real
**    name and nickname if the channel <mask> cannot be found.
**
**    If the "o" parameter is passed only operators are returned according
**    to the <mask> supplied.
**
**    Numeric Replies:
**
**            ERR_NOSUCHSERVER
**            RPL_WHOREPLY                  RPL_ENDOFWHO
**
**/

bool MasterServer::execWHO(std::string base, t_client_ParsedCmd &parsed_command)
{
	(void)base;
	(void)parsed_command;
	Client *client = parsed_command.first; // should not be null regarding how we got here

	lazyParsedSubType channels(((*(parsed_command.second))[CHANNELS]));
	for (lazyParsedSubType::iterator it = channels.begin(); it != channels.end(); it++)
	{
		Channel *chan = findChanneWithName(*it);
		if (!chan)
		{
			// no chan
			return true;
		}

		pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_WHOREPLY, this, client, &base, chan));
		pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_ENDOFWHO, this, client, &base, chan));
		// join one after the other
	}

	return true;
}
