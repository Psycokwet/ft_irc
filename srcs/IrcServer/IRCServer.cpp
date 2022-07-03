#include "IRCServer.hpp"

/*
** ---------------------------------- STATIC ----------------------------------
*/

t_commands_dictionary IRCServer::initCommandsDictionnary()
{
	t_commands_dictionary map;
	map["ADMIN"] = &IRCServer::example_command;
	map["AWAY"] = &IRCServer::example_command;
	map["DIE"] = &IRCServer::example_command;
	map["INVITE"] = &IRCServer::example_command;
	map["JOIN"] = &IRCServer::example_command;
	map["KICK"] = &IRCServer::example_command;
	map["KILL"] = &IRCServer::example_command;
	map["LIST"] = &IRCServer::example_command;
	map["MODE"] = &IRCServer::example_command;
	map["MOTD"] = &IRCServer::example_command;
	map["NAMES"] = &IRCServer::example_command;
	map["NICK"] = &IRCServer::execNICK;
	map["NOTICE"] = &IRCServer::example_command;
	map["OPER"] = &IRCServer::example_command;
	map["PART"] = &IRCServer::example_command;
	map["PASS"] = &IRCServer::execPASS;
	map["PING"] = &IRCServer::example_command;
	map["PRIVMSG"] = &IRCServer::example_command;
	map["QUIT"] = &IRCServer::example_command;
	map["TIME"] = &IRCServer::example_command;
	map["TOPIC"] = &IRCServer::example_command;
	map["USER"] = &IRCServer::execUSER;
	map["VERSION"] = &IRCServer::example_command;
	map["WHO"] = &IRCServer::example_command;
	// ignored commands
	map["CAP"] = &IRCServer::ignore_command;
	map["CNOTICE"] = &IRCServer::ignore_command;
	map["CPRIVMSG"] = &IRCServer::ignore_command;
	map["CONNECT"] = &IRCServer::ignore_command;
	map["ENCAP"] = &IRCServer::ignore_command;
	map["ERROR"] = &IRCServer::ignore_command;
	map["HELP"] = &IRCServer::ignore_command;
	map["INFO"] = &IRCServer::ignore_command;
	map["ISON"] = &IRCServer::ignore_command;
	map["KNOCK"] = &IRCServer::ignore_command;
	map["LINKS"] = &IRCServer::ignore_command;
	map["LUSERS"] = &IRCServer::ignore_command;
	map["NAMESX"] = &IRCServer::ignore_command;
	map["PONG"] = &IRCServer::ignore_command;
	map["REHASH"] = &IRCServer::ignore_command;
	map["RULES"] = &IRCServer::ignore_command;
	map["SERVER"] = &IRCServer::ignore_command;
	map["SERVICE"] = &IRCServer::ignore_command;
	map["SERVLIST"] = &IRCServer::ignore_command;
	map["SQUIT"] = &IRCServer::ignore_command;
	map["SETNAME"] = &IRCServer::ignore_command;
	map["SILENCE"] = &IRCServer::ignore_command;
	map["STATS"] = &IRCServer::ignore_command;
	map["SUMMON"] = &IRCServer::ignore_command;
	map["TRACE"] = &IRCServer::ignore_command;
	map["UHNAMES"] = &IRCServer::ignore_command;
	map["USERHOST"] = &IRCServer::ignore_command;
	map["USERIP"] = &IRCServer::ignore_command;
	map["USERS"] = &IRCServer::ignore_command;
	map["WALLOPS"] = &IRCServer::ignore_command;
	map["WATCH"] = &IRCServer::ignore_command;
	map["WHOIS"] = &IRCServer::ignore_command;
	map["WHOWAS"] = &IRCServer::ignore_command;

	return map;
}

t_commands_dictionary IRCServer::_commandsDictionnary = IRCServer::initCommandsDictionnary();
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
IRCServer::IRCServer(std::string const &password) : _serverPassword(password)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/
IRCServer::~IRCServer()
{
	std::map<int, User *>::iterator itUser;
	std::map<std::string, Channel *>::iterator itChannel;

	for (itUser = _users.begin(); itUser != _users.end(); ++itUser)
		delete itUser->second;
	for (itChannel = _channels.begin(); itChannel != _channels.end(); ++itChannel)
		delete itChannel->second;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- COMMANDS validated ---------------------------
*/

bool IRCServer::ignore_command(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)parsed_command;
	(void)respQueue;
	return true;
}

/*
** --------------------------------- COMMANDS thi-nguy ---------------------------
*/

/*
** --------------------------------- COMMANDS mida ---------------------------
*/

/*
** --------------------------------- PUBLIC METHODS ---------------------------
*/

void IRCServer::removeDisconnectUser(int fd)
{
	if (_users.find(fd) != _users.end())
	{
		User *one_user(_users[fd]);
		if (one_user->getRegistered() == true)
			removeUserFromAllChannels(one_user);
		delete one_user;
		_users.erase(fd);
	}
}

// Called by the server. Process a command from a client, then queue responses
// into responseQueue. Return true if client is disconnecting, otherwise false.
bool IRCServer::processCommand(t_client_ParsedCmd parsed_command, std::vector<t_clientCmd> &respQueue)
{
	(void)respQueue;
	bool isCommandExecuted = false;
	User *one_user;
	std::string cmd_name = ((*(parsed_command.second))[COMMAND]).front(); // if we got in here, we already check that there is something here
	int fd = parsed_command.first;
	(void)one_user;
	if (_users.find(fd) == _users.end()) // if a new user comes to server
	{
		// make new users, get Notice message, put it and the user, fd into responseQueue
		_users[fd] = new User(fd);
		one_user = _users[fd];
	}
	else
		one_user = _users[fd];

	for (t_commands_dictionary::iterator it = IRCServer::_commandsDictionnary.begin(); it != IRCServer::_commandsDictionnary.end(); it++)
	{
		if (it->first == cmd_name)
		{
			if (!(this->*(it->second))(parsed_command, respQueue))
			{
				// manage error case
				std::cout << " Command returned false, is there an error ?\n";
			}
			isCommandExecuted = true;
			break;
		}
	}
	if (!isCommandExecuted)
	{
		// should we send an error or something ?
		std::cout << "No command correspond to " << cmd_name << "\n";
	}
	delete parsed_command.second; // if NULL then we never got inside process command in the first place
	return false;
}

// Get the fd being killed by a server operator
int IRCServer::getVictim()
{
	int ret = _fdToKill;
	_fdToKill = -1;
	return ret;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/*
** --------------------------------- PRIVATE METHODS --------------------------
*/
void IRCServer::removeUserFromAllChannels(User *user)
{
	(void)user;
	// ! Erase user in the channel map
}

void IRCServer::pushToQueue(int fd, std::string const &msg, std::vector<t_clientCmd> &respQueue) const
{
	respQueue.push_back(std::make_pair(fd, msg));
}