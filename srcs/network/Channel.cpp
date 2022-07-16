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
bool Channel::kick(std::string name_victim, MasterServer *serv, Client *client, std::string notification)
{
	Client *victim = findClientWithNick(name_victim);

	if (!isOperatorHere(client))
	{
		serv->pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_CHANOPRIVSNEEDED, serv, client));
		return false;
	}
	if (!victim || !quit_part(serv, victim, "PART " + getName() + " Kicked by " + client->getNick() + " with motif " + notification))
	{
		serv->pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_USERNOTINCHANNEL, serv, client, &name_victim, this));
		return false;
	}
	return true;
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

bool Channel::isOperatorHere(Client *c)
{
	if (_clients.find(c->getFd()) == _clients.end())
		return false;
	return (HAS_TYPE(_clients[c->getFd()].second, _MOD_CHANNEL_FLAG_OPERATOR) || HAS_TYPE(_clients[c->getFd()].first->getMode(), _MOD_FLAG_OPERATOR));
}

Client *Channel::findClientWithNick(std::string nick)
{
	for (t_client_modes::const_iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->second.first->getNick() == nick)
			return it->second.first;
	}
	return NULL;
}

bool Channel::applyMode(std::string target_modes, MasterServer *serv, std::string base, t_client_ParsedCmd &parsed_command)
{
	(void)serv;
	(void)base;
	(void)parsed_command;
	Client *client = parsed_command.first; // should not be null regarding how we got here

	if (_clients.find(client->getFd()) == _clients.end())
	{
		serv->pushToQueue(client->getFd(), CodeBuilder::errorToString(ERR_USERNOTINCHANNEL, serv, client, &base, this));
		return false;
	}

	if (!isOperatorHere(client))
	{
		serv->pushToQueue(client->getFd(), CodeBuilder::errorToString(ERR_CHANOPRIVSNEEDED, serv, client, &base, this));
		return false;
	}
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
		if (!(this->*(Channel::charChannelModeDictionnary[*it].second))(add, serv, base, parsed_command))
			return false;
	}
	return true;
}

bool Channel::applyOperatorMode(bool add, MasterServer *serv, std::string base, t_client_ParsedCmd &parsed_command)
{
	(void)add;
	(void)serv;
	(void)base;
	(void)parsed_command;
	Client *client = parsed_command.first; // should not be null regarding how we got here

	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
	if (params.size() < 2)
	{
		serv->pushToQueue(client->getFd(), CodeBuilder::errorToString(ERR_NEEDMOREPARAMS, serv, client, &base, this));
		return false;
	}
	params.pop_front();
	for (lazyParsedSubType::iterator it = params.begin(); it != params.end(); it++)
	{
		Client *dest = findClientWithNick(*it);
		if (!dest)
		{
			serv->pushToQueue(client->getFd(), CodeBuilder::errorToString(ERR_USERNOTINCHANNEL, serv, client, &base, this));
			return false;
		}
		// copié collé de la flemme, bad
		bool success = false;
		if (add)
			success = addMode(dest->_fd, _MOD_CHANNEL_FLAG_OPERATOR);
		else
			success = minusMode(dest->_fd, _MOD_CHANNEL_FLAG_OPERATOR);
		if (success)
			serv->pushToQueue(dest->_fd, ":" + serv->getFullClientID(client) + " MODE " + dest->getNick() + " :" + (add ? "+" : "-") + "o" + END_OF_COMMAND);
	}

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
	return modeToString(); // modeToString(_modes); // need to implement for real
}
t_client_modes &Channel::getClients()
{
	return _clients;
}

bool Channel::addMode(int fd, e_mode_channel mode)
{
	if (_clients.find(fd) == _clients.end())
		return false;

	unsigned int tmp = _clients[fd].second;
	unsigned int new_modes = _clients[fd].second;
	new_modes = _clients[fd].second | mode;
	_clients[fd].second = static_cast<e_mode_channel>(new_modes);
	if (tmp != static_cast<unsigned int>(_clients[fd].second))
		return true;
	return false;
}
bool Channel::minusMode(int fd, e_mode_channel mode)
{
	if (_clients.find(fd) == _clients.end())
		return false;
	unsigned int tmp = _clients[fd].second;
	unsigned int new_modes = _clients[fd].second;
	new_modes = _clients[fd].second - (_clients[fd].second & mode);
	_clients[fd].second = static_cast<e_mode_channel>(new_modes);
	if (tmp != static_cast<unsigned int>(_clients[fd].second))
		return true;
	return false;
}

void Channel::setTopic(std::string new_topic)
{
	this->_topic = new_topic;
}

/* ************************************************************************** */