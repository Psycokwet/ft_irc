#include "Client.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Client::Client(int fd) : _fd(fd),
						 _passOK(false),
						 _registered(false),
						 _nick(UNDEFINED_NICK),
						 _realName(""),
						 _userOnHost("")
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

std::string Client::getNick() { return _nick; }
void Client::setRealName(std::string realName) { _realName = realName; }
std::string Client::getRealName() { return _realName; }
std::string Client::getUserOnHost() { return _userOnHost; }
int Client::getFd() { return _fd; }
