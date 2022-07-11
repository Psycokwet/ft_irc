#include "../network/MasterServer.hpp"

/*
** ---------------------------------- PING ----------------------------------
** Parameters: <server1> [ <server2> ]
**
**      The PING command is used to test the presence of an active client or
**   server at the other end of the connection.  Servers send a PING
**   message at regular intervals if no other activity detected coming
**   from a connection.  If a connection fails to respond to a PING
**   message within a set amount of time, that connection is closed.  A
**   PING message MAY be sent even if the connection is active.
**
**   When a PING message is received, the appropriate PONG message MUST be
**   sent as reply to <server1> (server which sent the PING message out)
**   as soon as possible.  If the <server2> parameter is specified, it
**   represents the target of the ping, and the message gets forwarded
**   there.
**
**   Numeric Replies:
**
**           ERR_NOORIGIN                  ERR_NOSUCHSERVER
**
**   Examples:
**  
**     PING tolsun.oulu.fi             ; server sending a PING message to
**										another server to indicate it is still
**										alive.
**  
**     PING WiZ tolsun.oulu.fi         ; Command from nick WiZ to send a PING
**                                     message to server "tolsun.oulu.fi"
**  
**     PING :irc.funet.fi              ; Ping message sent by server
**                                     "irc.funet.fi"
**
**	 Notes:
**	 Hexchat sends PING automatically to our server. OR Client can type: /ping or /PING on Hexchat.
**/

bool MasterServer::execPING(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)base;
	(void)parsed_command;
	(void)respQueue;
	Client *client = parsed_command.first; // should not be null regarding how we got here
	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
	lazyParsedSubType message(((*(parsed_command.second))[MESSAGE]));

	if (!message.size() && !params.size())
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOORIGIN, this, client, &base), respQueue);
		return true;
	}
	switch (params.size())
	{
		case 0:
			pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOSUCHSERVER, this, client, &base), respQueue);
			break;
		case 1:
			pushToQueue(client->_fd, ":" + getHost() + " PONG " + getHost() + " :" + params.front() + "\r\n", respQueue);
			break;
		default:
			pushToQueue(client->_fd, TOO_MANY_ARGS, respQueue); // not necessary regarding doc
			// too much params
			break;
	}
	return true;
}