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
**                                     #test.
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
	if (HAS_TYPE(client->getMode(), ))	   // Non tu dois voir le mode de CHANNEL pour ça thi-nguy :) Eventuellement, faut l'ajouter aux modes settable sur channel dans ce cas, sinon t'ignore juste et t'accepte que ça soit set

		lazyParsedSubType channels(((*(parsed_command.second))[CHANNELS]));
	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));

	std::cout << "Channel:" << channels.front() << std::endl;
	std::cout << "Channel:" << channels.front() << std::endl;

	Channel *current_chan = findChanneWithName(channels.front());
	if (!current_chan)
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOSUCHCHANNEL, this, client, &channels.front()));
		return true;
	}

	return true;
}
