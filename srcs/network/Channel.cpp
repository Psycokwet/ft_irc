#include "Channel.hpp"

/*
** ---------------------------------- STATIC ----------------------------------
*/

DEFINE_ENUM(e_mode_channel, E_MODE_CHANNEL_ENUM)

t_char_channel_mode_dictionary Channel::initCharChannelModeDictionnary()
{
	t_char_channel_mode_dictionary map;
	// map['O'] = std::make_pair(_MOD_CHANNEL_FLAG_CREATOR, NULL);
	map['o'] = std::make_pair(_MOD_CHANNEL_FLAG_OPERATOR, &Channel::applyOperatorMode);
	// map['v'] = std::make_pair(_MOD_CHANNEL_FLAG_VOICE, NULL);
	// map['a'] = std::make_pair(_MOD_CHANNEL_FLAG_ANONYMOUS, NULL);
	// map['i'] = std::make_pair(_MOD_CHANNEL_FLAG_INVITE_ONLY, NULL);
	// map['m'] = std::make_pair(_MOD_CHANNEL_FLAG_MODERATED, NULL);
	// map['n'] = std::make_pair(_MOD_CHANNEL_FLAG_NO_MESSAGE, NULL);

	// map['q'] = std::make_pair(_MOD_CHANNEL_FLAG_QUIET, NULL);
	// map['p'] = std::make_pair(_MOD_CHANNEL_FLAG_PRIVATE, NULL);
	// map['s'] = std::make_pair(_MOD_CHANNEL_FLAG_SECRET, NULL);
	// map['r'] = std::make_pair(_MOD_CHANNEL_FLAG_REOP, NULL);
	// map['t'] = std::make_pair(_MOD_CHANNEL_FLAG_TOPIC_SETTABLE, NULL);
	// map['k'] = std::make_pair(_MOD_CHANNEL_FLAG_KEY, NULL);
	// map['l'] = std::make_pair(_MOD_CHANNEL_FLAG_USER_LIMIT, NULL);
	// map['b'] = std::make_pair(_MOD_CHANNEL_FLAG_KEEP_OUT, NULL);
	// map['e'] = std::make_pair(_MOD_CHANNEL_FLAG_BAN_MASK, NULL);
	// map['I'] = std::make_pair(_MOD_CHANNEL_FLAG_INVITATION_MASK, NULL);
	return map;
};
t_char_channel_mode_dictionary Channel::charChannelModeDictionnary = Channel::initCharChannelModeDictionnary();

e_mode_channel Channel::stringToMode(std::string s)
{
	unsigned int tmp = _MOD_NO_FLAGS;
	size_t max = s.size();
	for (size_t i = 0; i < max; i++)
	{
		if (charChannelModeDictionnary.find(s[i]) == charChannelModeDictionnary.end())
			throw unknownModeException();
		// if (HAS_TYPE(tmp, charChannelModeDictionnary[s[i]]))
		// 	throw new doubleSetModeException(); //not a problem in the rfc
		tmp = tmp | charChannelModeDictionnary[s[i]].first;
	}
	return static_cast<e_mode_channel>(tmp);
}
void modeToStringInt(e_mode_channel type, void *raw)
{
	std::string *s = static_cast<std::string *>(raw);

	for (t_char_channel_mode_dictionary::iterator it = Channel::charChannelModeDictionnary.begin(); it != Channel::charChannelModeDictionnary.end(); it++)
	{
		if (it->second.first == type)
		{
			*s = *s + it->first;
			return;
		}
	}
}
std::string Channel::modeToString(e_mode_channel modes)
{
	std::string buff = "";
	iteratee_mode_channelEnum(modes, static_cast<void *>(&buff), &modeToStringInt);
	return buff;
}
std::string Channel::modeToString() const
{
	return modeToString(_modes);
}

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel(std::string name) : _name(name), _topic(""), _clients(t_client_modes()), _modes(_MOD_CHANNEL_NO_FLAGS)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Channel::~Channel()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/

std::string Channel::clientListToString(bool with_invisible)
{
	std::string acc = "";
	std::string sep = "";
	for (t_client_modes::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (with_invisible == false && HAS_TYPE((*it).second.first->getMode(), _MOD_FLAG_INVISIBLE))
			continue;
		acc += sep;
		if (isOperatorHere((*it).second.first))
			acc += "@";
		acc += (*it).second.first->getNick();
		sep = " ";
	}
	return acc;
}
void Channel::sendToWholeChannel(std::vector<t_clientCmd> &respQueue, MasterServer *serv, std::string message, Client *exclude)
{
	for (t_client_modes::const_iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (exclude && *exclude == *(it->second.first))
			continue;
		serv->pushToQueue(it->second.first->getFd(), message, respQueue);
	}
}

void Channel::join(std::vector<t_clientCmd> &respQueue, MasterServer *serv, Client *client)
{
	if (_clients.find(client->getFd()) != _clients.end())
		return;
	if (!_clients.size())
		_clients[client->getFd()] = std::make_pair(client, _MOD_CHANNEL_FLAG_OPERATOR);
	else
		_clients[client->getFd()] = std::make_pair(client, _MOD_CHANNEL_NO_FLAGS);
	serv->pushToQueue(client->getFd(), ":" + serv->getFullClientID(client) + " JOIN " + getName() + END_OF_COMMAND, respQueue);
	serv->pushToQueue(client->getFd(), CodeBuilder::errorToString(RPL_NAMREPLY, serv, client, NULL, this), respQueue);
	serv->pushToQueue(client->getFd(), CodeBuilder::errorToString(RPL_ENDOFNAMES, serv, client, NULL, this), respQueue);
	sendToWholeChannel(respQueue, serv, ":" + serv->getFullClientID(client) + " JOIN " + getName() + END_OF_COMMAND, client);
}
void Channel::quit(Client *client)
{
	if (_clients.find(client->getFd()) == _clients.end())
		return;
	_clients.erase(client->getFd());
}
std::string Channel::clientModesToString(Client *c)
{
	if (_clients.find(c->getFd()) == _clients.end())
		return "";
	return std::string("H") + (isOperatorHere(c) ? "@" : ""); // need to implement for real
}

bool Channel::isOperatorHere(Client *c)
{
	if (_clients.find(c->getFd()) == _clients.end())
		return false;
	return (HAS_TYPE(_clients[c->getFd()].second, _MOD_CHANNEL_FLAG_OPERATOR) || HAS_TYPE(_clients[c->getFd()].first->getMode(), _MOD_FLAG_OPERATOR));
}

bool Channel::applyMode(std::string target_modes, MasterServer *serv, std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)serv;
	(void)base;
	(void)parsed_command;
	(void)respQueue;

	bool add = true;
	if (target_modes.at(0) == '-' || target_modes.at(0) == '+')
	{
		if (target_modes.at(0) == '-')
			add = false;
		target_modes = target_modes.substr(1);
	}

	for (std::string::iterator it = target_modes.begin(); it != target_modes.end(); it++)
	{
		if (Channel::charChannelModeDictionnary.find(*it) == Channel::charChannelModeDictionnary.end())
		{ // print error
			return false;
		}
		if (!(this->*(Channel::charChannelModeDictionnary[*it].second))(add, serv, base, parsed_command, respQueue))
			return false;
	}
	return true;
}

bool Channel::applyOperatorMode(bool add, MasterServer *serv, std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)add;
	(void)serv;
	(void)base;
	(void)parsed_command;
	(void)respQueue;

	return true;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string Channel::getName()
{
	return "#" + _name;
}
std::string Channel::getTopic()
{
	return _topic;
}
std::string Channel::getModes()
{
	return "+t"; // modeToString(_modes); // need to implement for real
}
t_client_modes &Channel::getClients()
{
	return _clients;
}

/* ************************************************************************** */