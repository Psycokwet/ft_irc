#include "../network/MasterServer.hpp"

/*
** ---------------------------------- TOPIC ----------------------------------
**   Command: TOPIC
**     Parameters: <channel> [ <topic> ]
**
**     The TOPIC command is used to change or view the topic of a channel.
**     The topic for channel <channel> is returned if there is no <topic>
**     given.  If the <topic> parameter is present, the topic for that
**     channel will be changed, if this action is allowed for the user
**     requesting it.  If the <topic> parameter is an empty string, the
**     topic for that channel will be removed.
**
**     Numeric Replies:
**
**             ERR_NEEDMOREPARAMS              ERR_NOTONCHANNEL
**             RPL_NOTOPIC                     RPL_TOPIC
**             ERR_CHANOPRIVSNEEDED            ERR_NOCHANMODES
**
**     Examples:
**
**     :WiZ!jto@tolsun.oulu.fi TOPIC #test :New topic ; User Wiz setting the
**                                     topic.
**
**     TOPIC #test :another topic      ; Command to set the topic on #test
**                                     to "another topic".
**
**     TOPIC #test :                   ; Command to clear the topic on
**                                     #test. --> can not do this on Hexchat
**
**     TOPIC #test                     ; Command to check the topic for
**                                     #test.
**      Notes:
**          - Hexchat always add an `:` between channel's name and the contents.
*/

bool MasterServer::execTOPIC(std::string base, t_client_ParsedCmd &parsed_command)
{
	(void)base;
	(void)parsed_command;
	Client *client = parsed_command.first; // should not be null regarding how we got here
	lazyParsedSubType channels(((*(parsed_command.second))[CHANNELS]));
	lazyParsedSubType message(((*(parsed_command.second))[MESSAGE]));

	Channel *current_chan = findChanneWithName(channels.front());
	if (!current_chan)
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOSUCHCHANNEL, this, client, &base));
		return true;
	}
	std::stringstream ss;
	switch (message.size())
	{
	case 0:
		if (current_chan->getTopic() == "")
			pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_NOTOPIC, this, client, &base, current_chan));
		else
			pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_TOPIC, this, client, &base, current_chan));
		break;
	case 1:
		if (!current_chan->isOperatorHere(client))
		{
			pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_CHANOPRIVSNEEDED, this, client, &base, current_chan));
		}
		else
		{
			if (message.front() == ":")
			{
				current_chan->setTopic("");

				ss << ":" << getFullClientID(client) << " TOPIC #" << channels.front() << " :" << END_OF_COMMAND;
			}
			else
			{
				current_chan->setTopic(message.front());
				ss << ":" << getFullClientID(client) << " TOPIC #" << channels.front() << " :" << message.front() << END_OF_COMMAND;
			}
			sendToWholeServer(ss.str(), NULL);
		}
		break;
	default: // too much message
		break;
	}
	return true;
}
