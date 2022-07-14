#include "../network/MasterServer.hpp"

/*
** ---------------------------------- NAMES ----------------------------------
**  Command: NAMES
**  Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
**
**  By using the NAMES command, a user can list all nicknames that are
**  visible to him. For more details on what is visible and what is not,
**  see "Internet Relay Chat: Channel Management" [IRC-CHAN].  The
**  <channel> parameter specifies which channel(s) to return information
**  about.  There is no error reply for bad channel names.
**
**  If no <channel> parameter is given, a list of all channels and their
**  occupants is returned.  At the end of this list, a list of users who
**  are visible but either not on any channel or not on a visible channel
**  are listed as being on `channel' "*".
**
**  If the <target> parameter is specified, the request is forwarded to
**  that server which will generate the reply.
**  Wildcards are allowed in the <target> parameter.
**
**  Numerics:
**          ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
**          RPL_NAMREPLY                    RPL_ENDOFNAMES
**
**  353    RPL_NAMREPLY
**    ( "=" / "*" / "@" ) <channel> :[ "@" / "+" ] <nick> *( " " [ "@" / "+" ] <nick> )
**
**    - "@" is used for secret channels, "*" for private channels,
**          and "=" for others (public channels).
**
**  366    RPL_ENDOFNAMES
**    "<channel> :End of NAMES list"
**
**    - To reply to a NAMES message, a reply pair consisting
**          of RPL_NAMREPLY and RPL_ENDOFNAMES is sent by the
**          server back to the client.  If there is no channel
**          found as in the query, then only RPL_ENDOFNAMES is
**          returned.  The exception to this is when a NAMES
**          message is sent with no parameters and all visible
**          channels and contents are sent back in a series of
**          RPL_NAMEREPLY messages with a RPL_ENDOFNAMES to mark
**          the end.
**
**  Examples:
**  NAMES #twilight_zone,#42        ; Command to list visible users on
**                                  #twilight_zone and #42
**  NAMES                           ; Command to list all visible


**  Notes: Here we handle: no Chanel, no channel + no params, always get the first channel
**  user not in #chan, request /name #chan
*/

bool MasterServer::execNAMES(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)base;
	(void)parsed_command;
	(void)respQueue;
	Client *client = parsed_command.first; // should not be null regarding how we got here

	lazyParsedSubType channels(((*(parsed_command.second))[CHANNELS]));
	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));

	if (!channels.size()) // has no channel
	{
		if (params.size()) // This never happends on Hexchat because it always sends Names with something
		{
			pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_ENDOFNAMES, this, client, &params.front()), respQueue);
			return true;
		}
		// List all channels with their users.
		for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
		{
			Channel *chan = it->second;
			pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_NAMREPLY, this, client, &base, chan), respQueue);
		}
		pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_ENDOFNAMES, this, client, &base), respQueue);
		return true;
	}
	Channel *current_chan = findChanneWithName(channels.front());

	if (!current_chan)
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_ENDOFNAMES, this, client, &channels.front()), respQueue);
		return true;
	}

	//  List all users of that channel.
	pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_NAMREPLY, this, client, &base, current_chan), respQueue);
	pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_ENDOFNAMES, this, client, &base, current_chan), respQueue);
	return true;
}
