#include "MasterServer.hpp"

/*
** ---------------------------------- STATIC ----------------------------------
*/

t_commands_dictionary MasterServer::initCommandsDictionnary()
{
	t_commands_dictionary map;
	// connection registration
	map["PASS"] = std::make_pair(&Client::is_not_connected, &MasterServer::execPASS);
	map["USER"] = std::make_pair(&Client::is_connected, &MasterServer::execUSER);
	map["NICK"] = std::make_pair(&Client::is_connected, &MasterServer::execNICK);
	map["OPER"] = std::make_pair(&Client::is_registered, &MasterServer::execOPER);
	map["MODE"] = std::make_pair(&Client::is_registered, &MasterServer::execMODE);
	map["QUIT"] = std::make_pair(&Client::is_registered, &MasterServer::execQUIT);

	// channel operation
	map["JOIN"] = std::make_pair(&Client::is_registered, &MasterServer::execJOIN);
	map["PART"] = std::make_pair(&Client::is_registered, &MasterServer::execPART);
	// MODE too
	map["TOPIC"] = std::make_pair(&Client::is_registered, &MasterServer::execTOPIC);
	map["NAMES"] = std::make_pair(&Client::is_registered, &MasterServer::execNAMES);
	map["LIST"] = std::make_pair(&Client::is_registered, &MasterServer::execLIST);
	map["INVITE"] = std::make_pair(&Client::is_registered, &MasterServer::execINVITE);
	map["KICK"] = std::make_pair(&Client::is_registered, &MasterServer::execKICK);

	//  sending message
	map["PRIVMSG"] = std::make_pair(&Client::is_registered, &MasterServer::execPRIVMSG);
	map["NOTICE"] = std::make_pair(&Client::is_registered, &MasterServer::execPRIVMSG);

	//  Server queries and commands
	map["MOTD"] = std::make_pair(&Client::is_registered, &MasterServer::execMOTD);
	map["TIME"] = std::make_pair(&Client::is_registered, &MasterServer::execTIME);
	// map["VERSION"] = std::make_pair(&Client::is_not_connected, &MasterServer::execVERSION);
	map["ADMIN"] = std::make_pair(&Client::is_registered, &MasterServer::execADMIN);

	//  Miscellaneous messages
	map["KILL"] = std::make_pair(&Client::is_registered, &MasterServer::execKILL);
	map["PING"] = std::make_pair(&Client::is_registered, &MasterServer::execPING);

	//  Optional features
	map["AWAY"] = std::make_pair(&Client::is_registered, &MasterServer::execAWAY);
	map["DIE"] = std::make_pair(&Client::is_registered, &MasterServer::execDIE);

	//  user based queries
	map["WHO"] = std::make_pair(&Client::is_registered, &MasterServer::execWHO);

	// ignored commands
	map["CAP"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["CNOTICE"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["CPRIVMSG"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["CONNECT"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["ENCAP"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["ERROR"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["HELP"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["INFO"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["ISON"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["KNOCK"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["LINKS"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["LUSERS"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["NAMESX"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["PONG"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["REHASH"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["RULES"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["SERVER"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["SERVICE"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["SERVLIST"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["SQUIT"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["SETNAME"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["SILENCE"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["STATS"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["SUMMON"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["TRACE"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["UHNAMES"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["USERHOST"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["USERIP"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["USERS"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["WALLOPS"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["WATCH"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["WHOIS"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	map["WHOWAS"] = std::make_pair(&Client::always_true, &MasterServer::ignore_command);
	return map;
}

t_commands_dictionary MasterServer::_commandsDictionnary = MasterServer::initCommandsDictionnary();

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

MasterServer::MasterServer(int port, std::string const &password) : _fdServer(-1),
																	_maxFD(-1),
																	_port(port),
																	_password(password)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

MasterServer::~MasterServer()
{
	util_delete(_clients);
	util_delete(_channels);

	for (std::set<int>::iterator itDisconnect = _disconnectList.begin(); itDisconnect != _disconnectList.end(); ++itDisconnect)
		removeClient(*itDisconnect);
	_disconnectList.clear();
	_respQueue.clear();
	_command_list.clear();
	close(_fdServer);
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- PUBLIC METHODS ---------------------------
*/

int MasterServer::build()
{
	int opt = TRUE;
	struct sockaddr_in address;

	/************************************************************
	 * Create an AF_INET stream socket to receive incoming
	 * connections on
	 * If PROTOCOL is zero, one is chosen automatically.
	 * Returns a file descriptor for the new socket, or -1 for errors.
	 *************************************************************/
	_fdServer = socket(AF_INET, SOCK_STREAM, 0); // SOCK_NONBLOCK, 0);
	if (_fdServer == -1)
	{
		std::cerr << "Fail to set socket" << std::endl;
		return EXIT_FAILURE;
	}

/*************************************************************/
/* Allow socket descriptor to be reuseable                   */
/*************************************************************/
#ifdef __APPLE__
	if (setsockopt(_fdServer, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) == -1)
#else
	if (setsockopt(_fdServer, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, (char *)&opt, sizeof(opt)) == -1)
#endif
	{
		std::cerr << "setsockopt() failed" << std::endl;
		return EXIT_FAILURE;
	}

	/*************************************************************/
	/* Set address (host) and port                               */
	/*************************************************************/
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(_port);

	/*************************************************************/
	/* Bind the socket                                           */
	/*************************************************************/
	if (bind(_fdServer, (sockaddr *)&address, sizeof(address)) == -1)
	{
		std::cerr << "Fail to bind to port " << _port << std::endl;
		return EXIT_FAILURE;
	}

	/*************************************************************/
	/* Try to specify maximun of client pending connection for   */
	/*   the master socket (server_fd)                           */
	/*************************************************************/
	if (listen(_fdServer, MAX_CLIENT_QUEUE) == -1)
	{
		std::cerr << "Fail to listen" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Listening on port "
			  << _port
			  << std::endl;

	_maxFD = MAX(_maxFD, _fdServer);

	return EXIT_SUCCESS;
}

void MasterServer::run() // ! do like main_loops
{
	int total_opened_fd;
	while (TRUE)
	{
		_respQueue.clear();
		_disconnectList.clear();
		total_opened_fd = setFDForReading();
		if (total_opened_fd == -1)
			break;
		recvProcess(total_opened_fd);

		for (std::vector<t_clientCmd>::iterator itRes = _respQueue.begin(); itRes != _respQueue.end(); ++itRes)
		{
			int clientFd = itRes->first;
			if (_clients.find(clientFd) != _clients.end())
				if (!_clients[clientFd]->sendResp(itRes->second))
					_disconnectList.insert(clientFd);
		}

		for (std::set<int>::iterator itDisconnect = _disconnectList.begin(); itDisconnect != _disconnectList.end(); ++itDisconnect)
			removeClient(*itDisconnect);
	}
}

/*
** ------------------------- PRIVATE METHODS ----------------------------------
*/
bool MasterServer::processCommand(std::string base, t_client_ParsedCmd parsed_command)
{
	std::string cmd_name = ((*(parsed_command.second))[COMMAND]).front(); // if we got in here, we already check that there is something here
	for (t_commands_dictionary::iterator it = MasterServer::_commandsDictionnary.begin(); it != MasterServer::_commandsDictionnary.end(); it++)
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
			if (!(this->*(it->second.second))(base, parsed_command))
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
	return true;
}

int MasterServer::setFDForReading()
{
	_maxFD = MAX(_maxFD, _fdServer);
	FD_ZERO(&_fdReader);
	FD_SET(_fdServer, &_fdReader);

	std::map<int, Client *>::iterator clientIter;
	for (clientIter = _clients.begin(); clientIter != _clients.end(); ++clientIter)
	{
		int clientFD = clientIter->first;
		FD_SET(clientFD, &_fdReader);
		_maxFD = MAX(_maxFD, clientFD);
	}
	/*************************************************************/
	/* Call select() and wait 1 minutes for it to complete.      */
	/* Wait for one or more fd become "ready" to read and write  */
	/*************************************************************/
	int new_r;
	new_r = select(_maxFD + 1, &_fdReader, NULL, NULL, NULL);
	if (new_r == -1)
	{
		std::cout << "Error: select()\n";
		return (-1);
	}
	return new_r;
}

bool isLegalCmd(lazyParsedType **lad)
{
	if ((*lad)->find(COMMAND) == (*lad)->end())
	{
		delete (*lad);
		*lad = NULL;
		return false;
	}
	return true;
}

void MasterServer::recvProcess(int totalFd)
{
	// Checking each socket for reading, starting from FD 3 because there should be nothing
	// to read from 0 (stdin), 1 (stdout) and 2 (stderr)

	for (int fd = 3; fd <= _maxFD && totalFd; ++fd)
	{
		if (FD_ISSET(fd, &_fdReader))
		{
			--totalFd;
			if (fd == _fdServer) // if fd is Server
			{
				acceptClient(fd);
				continue;
			}
			else if (_disconnectList.find(fd) != _disconnectList.end()) // if fd client is not in disconnected list
				continue;

			lazyParsedType *parsed_command;
			bool ret = _clients[fd]->receiveCommand();

			if (ret == false)
			{
				// _disconnectList.insert(fd);
				// _MasterServer.removeDisconnectUser(fd);
				removeClient(fd);
				continue;
			}
			_command_list.clear();
			_command_list = stringToListKeepTokenizer(_clients[fd]->_received_command, END_OF_COMMAND);
			_clients[fd]->_received_command.clear();
			for (std::list<std::string>::iterator it = _command_list.begin(); it != _command_list.end(); it++)
			{
				std::string base = removeTokenAtEnd(*it, END_OF_COMMAND);
				if (it->size() == 0)
					continue;
				else if (!(parsed_command = LazyRequestParser(*it)) //
						 || !isLegalCmd(&parsed_command)			//
						 || !processCommand(base, std::make_pair(_clients[fd], parsed_command)))
				{
					_disconnectList.insert(fd);
					break; // if a false, then stop treating client
				}
			}
		}
	}
}

/*
** --------------------------------- CLIENTS management ---------------------------------
*/

void MasterServer::sendToWholeServer(std::string message, Client *exclude)
{
	for (std::map<int, Client *>::const_iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (exclude && *exclude == *(it->second))
			continue;
		pushToQueue(it->second->getFd(), message);
	}
}

void MasterServer::acceptClient(int fdServer)
{
	sockaddr_in sin;
	socklen_t sin_len = 0;

	int clientFD = accept(fdServer, (sockaddr *)&sin, &sin_len);
	if (clientFD == -1)
	{
		std::cerr << "Failed to accept a new connection\n";
		return;
	}
	std::cout << "New client on socket #" << clientFD
			  << std::endl;
	_clients.insert(std::make_pair(clientFD, new Client(clientFD)));
}

void MasterServer::removeClient(int fdClient)
{
	if (_clients.find(fdClient) != _clients.end())
	{
		for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
			it->second->quit_part(this, _clients[fdClient], "PART " + it->second->getName() + " :disconnected");
		delete _clients[fdClient];
		_clients.erase(fdClient);
	}
}

void MasterServer::pushToQueue(int fd, std::string const &msg)
{
	_respQueue.push_back(std::make_pair(fd, msg));
}
std::string MasterServer::getFullClientID(Client *c) const
{
	return c->getNick() + "!" + c->getUserOnHost() + "@" + getHost();
}
Client *MasterServer::findClientWithNick(std::string nick)
{
	for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		if (it->second->getNick() == nick)
			return it->second;
	return NULL;
}

/*
** --------------------------------- CHANNEL management ---------------------------------
*/
Channel *MasterServer::findChanneWithName(std::string name)
{
	return _channels[name];
}
Channel *MasterServer::createChannel(std::string name)
{
	if (_channels[name])
		return NULL;
	_channels[name] = new Channel(name);
	return _channels[name];
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string MasterServer::getHost() const
{
	return HOST;
}
std::string MasterServer::getServerName() const
{
	return SERVER_NAME;
}
std::string MasterServer::getServerVersion() const
{
	return SERVER_VERSION;
}
std::string MasterServer::getCreationDate() const
{
	return SERVER_CREATION_DATE;
}
std::string MasterServer::getAvailableUserModes() const
{
	return "biklmnopstv";
}
std::string MasterServer::getAvailableChannelModes() const
{
	return "ikot";
}
/* ************************************************************************* */
