#include "IRCServer.hpp"

/*
** ---------------------------------- STATIC ----------------------------------
*/

t_commands_dictionary IRCServer::initCommandsDictionnary()
{
	t_commands_dictionary map;
	map["ADMIN"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["AWAY"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["DIE"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["INVITE"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["JOIN"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["KICK"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["KILL"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["LIST"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["MODE"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["MOTD"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["NAMES"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["NICK"] = std::make_pair(&Client::is_connected, &IRCServer::execNICK);
	map["NOTICE"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["OPER"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["PART"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["PASS"] = std::make_pair(&Client::is_not_connected, &IRCServer::execPASS);
	map["PING"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["PRIVMSG"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["QUIT"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["TIME"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["TOPIC"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["USER"] = std::make_pair(&Client::is_connected, &IRCServer::execUSER);
	map["VERSION"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	map["WHO"] = std::make_pair(&Client::is_connected, &IRCServer::example_command);
	// ignored commands
	map["CAP"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["CNOTICE"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["CPRIVMSG"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["CONNECT"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["ENCAP"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["ERROR"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["HELP"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["INFO"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["ISON"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["KNOCK"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["LINKS"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["LUSERS"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["NAMESX"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["PONG"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["REHASH"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["RULES"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["SERVER"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["SERVICE"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["SERVLIST"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["SQUIT"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["SETNAME"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["SILENCE"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["STATS"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["SUMMON"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["TRACE"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["UHNAMES"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["USERHOST"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["USERIP"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["USERS"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["WALLOPS"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["WATCH"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["WHOIS"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	map["WHOWAS"] = std::make_pair(&Client::always_true, &IRCServer::ignore_command);
	return map;
}

t_commands_dictionary IRCServer::_commandsDictionnary = IRCServer::initCommandsDictionnary();
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
IRCServer::IRCServer(std::string const &password) : _clients(), _serverPassword(password)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/
IRCServer::~IRCServer()
{
	util_delete(_clients);
	// std::map<std::string, Channel *>::iterator itChannel;

	// for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	// 	delete it->second;
	// for (itChannel = _channels.begin(); itChannel != _channels.end(); ++itChannel)
	// 	delete itChannel->second;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- PUBLIC METHODS ---------------------------
*/

// void IRCServer::removeDisconnectUser(int fd)
// {
// 	if (_users.find(fd) != _users.end())
// 	{
// 		User *one_user(_users[fd]);
// 		if (one_user->getRegistered() == true)
// 			removeUserFromAllChannels(one_user);
// 		delete one_user;
// 		_users.erase(fd);
// 	}
// }

// Called by the server. Process a command from a client, then queue responses
// into responseQueue. Return true if client is disconnecting, otherwise false.
bool IRCServer::processCommand(std::string base, t_client_ParsedCmd parsed_command, std::vector<t_clientCmd> &respQueue)
{
	// User *one_user;
	std::string cmd_name = ((*(parsed_command.second))[COMMAND]).front(); // if we got in here, we already check that there is something here
	// int fd = parsed_command.first->get_fd();
	// (void)one_user;
	// if (_users.find(fd) == _users.end()) // make new users, get Notice message, put it and the user, fd into responseQueue
	// 	_users[fd] = new User(fd);
	// one_user = _users[fd];
	for (t_commands_dictionary::iterator it = IRCServer::_commandsDictionnary.begin(); it != IRCServer::_commandsDictionnary.end(); it++)
	{
		if (it->first == cmd_name)
		{
			if (!((parsed_command.first)->*(it->second.first))())
			{
				delete parsed_command.second; // if NULL then we never got inside process command in the first place

				// manage error or end process case
				std::cout << "Command not valid at this point of client use, ignore.\n";
				return true;
			}
			if (!(this->*(it->second.second))(base, parsed_command, respQueue))
			{
				delete parsed_command.second; // if NULL then we never got inside process command in the first place

				// manage error or end process case
				std::cout << "Command returned false, must quit client processing.\n";
				return false;
			}
			std::cout << "Command " << cmd_name << " done\n";
			delete parsed_command.second; // if NULL then we never got inside process command in the first place
			return true;
		}
	}
	std::cout << "No command correspond to " << cmd_name << ", ignoring it.\n";
	delete parsed_command.second; // if NULL then we never got inside process command in the first place
	return false;
}

// Get the fd being killed by a server operator
// int IRCServer::getVictim()
// {
// 	int ret = _fdToKill;
// 	_fdToKill = -1;
// 	return ret;
// }

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string IRCServer::getHost() const
{
	return HOST;
}
std::string IRCServer::getServerName() const
{
	return SERVER_NAME;
}
std::string IRCServer::getServerVersion() const
{
	return SERVER_VERSION;
}
std::string IRCServer::getCreationDate() const
{
	return SERVER_CREATION_DATE;
}
std::string IRCServer::getAvailableUserModes() const
{
	return "jesaispas";
}
std::string IRCServer::getAvailableChannelModes() const
{
	return "jesaispas";
}

/*
** --------------------------------- PRIVATE METHODS --------------------------
*/
// void IRCServer::removeUserFromAllChannels(User *user)
// {
// 	(void)user;
// 	// ! Erase user in the channel map
// }

void IRCServer::pushToQueue(int fd, std::string const &msg, std::vector<t_clientCmd> &respQueue) const
{
	respQueue.push_back(std::make_pair(fd, msg));
}
std::string IRCServer::getFullClientID(Client *c) const
{
	return c->getNick() + "!" + c->getUserOnHost() + "@" + getHost();
}
bool IRCServer::isNickAvailable(std::string new_nick)
{
	for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		if (it->second->getNick() == new_nick)
			return false;
	return true;
}
