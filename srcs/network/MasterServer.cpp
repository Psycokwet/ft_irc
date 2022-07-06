#include "MasterServer.hpp"

/*
** ---------------------------------- STATIC ----------------------------------
*/

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

MasterServer::MasterServer(int port, std::string const &password, IRCServer &irc) : _fdServer(-1),
																					_maxFD(-1),
																					_ircServer(irc),
																					_port(port),
																					_password(password)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

MasterServer::~MasterServer()
{
	std::map<int, Client *>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
		delete it->second;
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
	if (setsockopt(_fdServer, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, (char *)&opt, sizeof(opt)) == -1)
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
	std::vector<t_clientCmd> responseQueue;
	std::vector<t_clientCmd>::iterator itRes;
	std::set<int> disconnectList;
	std::set<int>::iterator itDisconnect;

	while (TRUE)
	{
		responseQueue.clear();
		disconnectList.clear();
		total_opened_fd = setFDForReading();
		if (total_opened_fd == -1)
			break;
		recvProcess(total_opened_fd, responseQueue, disconnectList);

		for (itRes = responseQueue.begin(); itRes != responseQueue.end(); ++itRes)
		{
			int clientFd = itRes->first;
			if (_clients.find(clientFd) != _clients.end())
				_clients[clientFd]->sendResp(itRes->second);
		}

		for (itDisconnect = disconnectList.begin(); itDisconnect != disconnectList.end(); ++itDisconnect)
			removeClient(*itDisconnect);
	}
}

/*
** ------------------------- PRIVATE METHODS ----------------------------------
*/

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

void MasterServer::recvProcess(int totalFd, std::vector<t_clientCmd> &resQueue, std::set<int> &disconnectList)
{
	// Checking each socket for reading, starting from FD 3 because there should be nothing
	// to read from 0 (stdin), 1 (stdout) and 2 (stderr)

	std::string received_command;
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
			else if (disconnectList.find(fd) != disconnectList.end()) // if fd client is not in disconnected list
				continue;

			received_command.clear();
			lazyParsedType *parsed_command;
			bool ret = _clients[fd]->receiveCommand(received_command);

			std::list<std::string> command_list(stringToListKeepTokenizer(received_command, CMD_SEP));
			for (std::list<std::string>::iterator it = command_list.begin(); it != command_list.end(); it++)
			{
				if (it->size() == 0)
					continue;
				if (ret == false)
				{
					_ircServer.removeDisconnectUser(fd);
					removeClient(fd);
				}
				else if (!(parsed_command = LazyRequestParser(*it)) //
						 || !isLegalCmd(&parsed_command)			//
						 || !_ircServer.processCommand(std::make_pair(fd, parsed_command), resQueue))
				{
					disconnectList.insert(fd);
					break; // if a false, then stop treating client
				}
				// int killed_by_operater_fd = _ircServer.getVictim();
				// if (killed_by_operater_fd != -1)
				// 	disconnectList.insert(killed_by_operater_fd);
			}
		}
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
		delete _clients[fdClient];
		_clients.erase(fdClient);
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************* */
