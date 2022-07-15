#include "Channel.hpp"

/*
** ---------------------------------- STATIC ----------------------------------
*/

DEFINE_ENUM(e_mode_channel, E_MODE_CHANNEL_ENUM)

t_char_channel_mode_dictionary Channel::initCharChannelModeDictionnary()
{
	t_char_channel_mode_dictionary map;
	map['O'] = std::make_pair(_MOD_CHANNEL_FLAG_CREATOR, false);
	map['o'] = std::make_pair(_MOD_CHANNEL_FLAG_OPERATOR, false);
	map['v'] = std::make_pair(_MOD_CHANNEL_FLAG_VOICE, false);
	map['a'] = std::make_pair(_MOD_CHANNEL_FLAG_ANONYMOUS, false);
	map['i'] = std::make_pair(_MOD_CHANNEL_FLAG_INVITE_ONLY, false);
	map['m'] = std::make_pair(_MOD_CHANNEL_FLAG_MODERATED, false);
	map['n'] = std::make_pair(_MOD_CHANNEL_FLAG_NO_MESSAGE, false);

	map['q'] = std::make_pair(_MOD_CHANNEL_FLAG_QUIET, false);
	map['p'] = std::make_pair(_MOD_CHANNEL_FLAG_PRIVATE, false);
	map['s'] = std::make_pair(_MOD_CHANNEL_FLAG_SECRET, false);
	map['r'] = std::make_pair(_MOD_CHANNEL_FLAG_REOP, false);
	map['t'] = std::make_pair(_MOD_CHANNEL_FLAG_TOPIC_SETTABLE, false);
	map['k'] = std::make_pair(_MOD_CHANNEL_FLAG_KEY, false);
	map['l'] = std::make_pair(_MOD_CHANNEL_FLAG_USER_LIMIT, false);
	map['b'] = std::make_pair(_MOD_CHANNEL_FLAG_KEEP_OUT, false);
	map['e'] = std::make_pair(_MOD_CHANNEL_FLAG_BAN_MASK, false);
	map['I'] = std::make_pair(_MOD_CHANNEL_FLAG_INVITATION_MASK, false);
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
bool Channel::isOperatorHere(Client *c)
{
	if (_clients.find(c->getFd()) == _clients.end())
		return false;
	return HAS_TYPE(_clients[c->getFd()].second, _MOD_CHANNEL_FLAG_OPERATOR) || HAS_TYPE(_clients[c->getFd()].first->getMode(), _MOD_FLAG_OPERATOR);
}
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
void Channel::sendToWholeChannel(MasterServer *serv, std::string message, Client *exclude)
{
	for (t_client_modes::const_iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (exclude && *exclude == *(it->second.first))
			continue;
		serv->pushToQueue(it->second.first->getFd(), message);
	}
}

void Channel::join(MasterServer *serv, Client *client)
{
	if (_clients.find(client->getFd()) != _clients.end())
		return;
	if (!_clients.size())
		_clients[client->getFd()] = std::make_pair(client, _MOD_CHANNEL_FLAG_OPERATOR);
	else
		_clients[client->getFd()] = std::make_pair(client, _MOD_CHANNEL_NO_FLAGS);
	serv->pushToQueue(client->getFd(), ":" + serv->getFullClientID(client) + " JOIN " + getName() + END_OF_COMMAND);
	serv->pushToQueue(client->getFd(), CodeBuilder::errorToString(RPL_NAMREPLY, serv, client, NULL, this));
	serv->pushToQueue(client->getFd(), CodeBuilder::errorToString(RPL_ENDOFNAMES, serv, client, NULL, this));
	sendToWholeChannel(serv, ":" + serv->getFullClientID(client) + " JOIN " + getName() + END_OF_COMMAND, client);
}
bool Channel::quit(Client *client)
{
	if (_clients.find(client->getFd()) == _clients.end())
		return false;
	_clients.erase(client->getFd());
	return true;
}
bool Channel::quit_part(MasterServer *serv, Client *client, std::string base)
{
	if (!quit(client))
		return false;
	serv->pushToQueue(client->getFd(), ":" + serv->getFullClientID(client) + " " + base + END_OF_COMMAND);
	sendToWholeChannel(serv, ":" + serv->getFullClientID(client) + " " + base + END_OF_COMMAND, client);
	return true;
}

std::string Channel::clientModesToString(Client *c)
{
	if (_clients.find(c->getFd()) == _clients.end())
		return "";
	return std::string("H") + (isOperatorHere(c) ? "@" : ""); // need to implement for real
}

Client *Channel::findClientWithNick(std::string nick)
{
	for (t_client_modes::iterator it = _clients.begin(); it != _clients.end(); ++it)
		if (it->second.first->getNick() == nick)
			return it->second.first;
	return NULL;
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