#include "Client.hpp"

/*
** ---------------------------------- STATIC ----------------------------------
*/

DEFINE_ENUM(e_mode_client, E_MODE_CLIENT_ENUM)

/* _MOD_FLAG_ADMIN		 					  none - user is flagged as away;
** _MOD_FLAG_AWAY		 					  a - user is flagged as away;
** _MOD_FLAG_INVISIBLE		 				  i - marks a users as invisible;
** _MOD_FLAG_WALLOPS						  w - user receives wallops;
** _MOD_FLAG_RESTRICTED		 				  r - restricted user connection;
** _MOD_FLAG_OPERATOR		 				  o - operator flag;
** _MOD_FLAG_LOCAL_OPERATOR		 			  O - local operator flag;
** _MOD_FLAG_SERVER_NOTICES_RECEIVR		 	  s - marks a user for receipt of server notices.
*/

t_char_client_mode_dictionary Client::initCharClientModeDictionnary()
{
	t_char_client_mode_dictionary map;
	map['a'] = std::make_pair(_MOD_FLAG_AWAY, false);
	map['i'] = std::make_pair(_MOD_FLAG_INVISIBLE, true);
	map['w'] = std::make_pair(_MOD_FLAG_WALLOPS, false);
	map['r'] = std::make_pair(_MOD_FLAG_RESTRICTED, false);
	map['o'] = std::make_pair(_MOD_FLAG_OPERATOR, false);
	map['O'] = std::make_pair(_MOD_FLAG_LOCAL_OPERATOR, false);
	map['s'] = std::make_pair(_MOD_FLAG_SERVER_NOTICES_RECEIVR, false);
	return map;
};
t_char_client_mode_dictionary Client::charClientModeDictionnary = Client::initCharClientModeDictionnary();

e_mode_client Client::stringToMode(std::string s)
{
	unsigned int tmp = _MOD_NO_FLAGS;
	size_t max = s.size();
	for (size_t i = 0; i < max; i++)
	{
		if (charClientModeDictionnary.find(s[i]) == charClientModeDictionnary.end())
			throw unknownModeException();
		// if (HAS_TYPE(tmp, charClientModeDictionnary[s[i]]))
		// 	throw new doubleSetModeException(); //not a problem in the rfc
		tmp = tmp | charClientModeDictionnary[s[i]].first;
	}
	return static_cast<e_mode_client>(tmp);
}
e_mode_client Client::stringToClientSettableMode(std::string s)
{
	unsigned int tmp = _MOD_NO_FLAGS;
	size_t max = s.size();
	for (size_t i = 0; i < max; i++)
	{
		if (charClientModeDictionnary.find(s[i]) == charClientModeDictionnary.end())
			throw unknownModeException();
		// if (HAS_TYPE(tmp, charClientModeDictionnary[s[i]]))
		// 	throw new doubleSetModeException(); //not a problem in the rfc
		if (charClientModeDictionnary[s[i]].second)
			tmp = tmp | charClientModeDictionnary[s[i]].first;
	}
	return static_cast<e_mode_client>(tmp);
}
void modeToStringInt(e_mode_client type, void *raw)
{
	std::string *s = static_cast<std::string *>(raw);

	for (t_char_client_mode_dictionary::iterator it = Client::charClientModeDictionnary.begin(); it != Client::charClientModeDictionnary.end(); it++)
	{
		if (it->second.first == type)
		{
			*s = *s + it->first;
			return;
		}
	}
}
std::string Client::modeToString(e_mode_client modes)
{
	std::string buff = "";
	iteratee_mode_clientEnum(modes, static_cast<void *>(&buff), &modeToStringInt);
	return buff;
}
std::string Client::modeToString() const
{
	return modeToString(_modes);
}

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Client::Client(int fd) : _fd(fd),
						 _passOK(false),
						 _registered(false),
						 _oper(false),
						 _nick(UNDEFINED_NICK),
						 _realName(""),
						 _userOnHost(""),
						 _modes(_MOD_NO_FLAGS)
{
}

Client::~Client()
{
	std::cout << "Remove client " << _fd << std::endl;
	close(_fd);
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

bool Client::operator==(const Client &rhs) const
{
	return _fd == rhs._fd;
}

/*
** ------------------------- PRIVATE METHODS ----------------------------------
*/

bool Client::receiveCommand(std::string &command)
{
	ssize_t r = recv(_fd, _buffer, BUF_SIZE, 0);
	if (r <= 0)
		return false;
	_buffer[r] = '\0';

	_commandTemp += _buffer;

	std::size_t found = _commandTemp.find(END_OF_COMMAND, _commandTemp.size() - LEN_END_OF_COMMAND);
	if (found != std::string::npos)
	{
		command = _commandTemp;
		_commandTemp.clear();
	}
	return true;
}

void Client::sendResp(std::string const &resp)
{
	send(_fd, resp.c_str(), resp.size(), 0);
}

bool Client::always_true()
{
	return true;
}
bool Client::always_false()
{
	return false;
}
bool Client::is_not_connected()
{
	return !is_connected();
}
bool Client::is_connected()
{
	return _passOK;
}
bool Client::is_registered()
{
	return _passOK && _registered;
}

void Client::validatedRegistration(std::vector<t_clientCmd> &respQueue, MasterServer *serv)
{
	if (_nick == UNDEFINED_NICK || _userOnHost == "")
		return;
	serv->pushToQueue(_fd, CodeBuilder::errorToString(RPL_WELCOME, serv, this), respQueue);
	serv->pushToQueue(_fd, CodeBuilder::errorToString(RPL_YOURHOST, serv, this), respQueue);
	serv->pushToQueue(_fd, CodeBuilder::errorToString(RPL_CREATED, serv, this), respQueue);
	serv->pushToQueue(_fd, CodeBuilder::errorToString(RPL_MYINFO, serv, this), respQueue);
	_registered = true;
}

/*
** ------------------------- ACCESSORS ----------------------------------
*/

std::string Client::getNick() const { return _nick; }
void Client::setRealName(std::string realName) { _realName = realName; }
std::string Client::getRealName() const { return _realName; }
std::string Client::getUserOnHost() const { return _userOnHost; }
int Client::getFd() { return _fd; }
e_mode_client Client::getMode() const { return _modes; }
void Client::setMode(e_mode_client mode) { _modes = mode; }
bool Client::addMode(e_mode_client mode)
{
	unsigned int tmp = _modes;
	unsigned int new_modes = _modes;
	new_modes = _modes | mode;
	_modes = static_cast<e_mode_client>(new_modes);
	if (tmp != _modes)
		return true;
	return false;
}
bool Client::minusMode(e_mode_client mode)
{
	unsigned int tmp = _modes;
	unsigned int new_modes = _modes;
	new_modes = _modes - (_modes & mode);
	_modes = static_cast<e_mode_client>(new_modes);
	if (tmp != _modes)
		return true;
	return false;
}
