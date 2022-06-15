#include "MasterServer.hpp"

/*
** ---------------------------------- STATIC ----------------------------------
*/


/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

MasterServer::MasterServer(int port, std::string const & password, IRCServer &irc) :
	_fdServer(-1),
	_maxFD(-1),
	_ircServer(irc),
	_port(port),
	_password(password)
{}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

MasterServer::~MasterServer()
{
	std::map<int, Client *>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
		delete it->second;
	close (_fdServer);
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- PUBLIC METHODS ----------------------------------
*/

std::ostream &MasterServer::print_client_map(std::ostream &o) const
{
	o << "I'm Client Map !" << std::endl;
	std::map<int, Client *>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		o << "Client fd: " << it->first;
		
	}
	return o;
}

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
	_fdServer = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
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
		return EXIT_FAILURE ;
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
		return EXIT_FAILURE ;
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

	std::cout	<< "Listening on port "
				<< _port
				<< std::endl;

	_maxFD = MAX(_maxFD, _fdServer);

    return EXIT_SUCCESS;
}

void MasterServer::run() // ! do like main_loops
{
    while (TRUE)
    {
        FD_ZERO(&_fdReader);
        setFDForReading();
        recvProcess();
    }
}

/*
** ------------------------- PRIVATE METHODS ----------------------------------
*/

void	MasterServer::setFDForReading()
{
	//  std::map<int, std::pair<OneServer*, std::map <int, GrammarParser> > >::iterator it;
	 std::map<int, std::pair<OneServer*, std::map <int, std::string> > >::iterator it;
	for (it = _fdMap.begin(); it!=_fdMap.end(); ++it)
	{
		int 			fdServer = it->first;
		// std::map <int, GrammarParser> 	fdClientMap = it->second.second;
		std::map <int, std::string> 	fdClientMap = it->second.second;

		_maxFD = MAX(_maxFD, fdServer);
		FD_SET(fdServer, &_fdReader);

		// std::map <int, GrammarParser>::iterator	clientIter;
		std::map <int, std::string>::iterator	clientIter;
		for (clientIter = fdClientMap.begin(); clientIter != fdClientMap.end(); ++clientIter)
		{
			int	clientFD = clientIter->first;
			FD_SET(clientFD, &_fdReader);
			_maxFD = MAX(_maxFD, clientFD);
		}
	}

    struct timeval      timeout;
    /*************************************************************/
    /* Initialize the timeval struct to 1 minutes.               */
    /*************************************************************/
    timeout.tv_sec = 1 * 60;
    timeout.tv_usec = 0;
    /*************************************************************/
    /* Call select() and wait 1 minutes for it to complete.      */
    /* Wait for one or more fd become "ready" to read and write  */
    /*************************************************************/
	int new_r;
	new_r = select(_maxFD + 1, &_fdReader, NULL, NULL, &timeout);
	if (new_r == -1)
		SERVER_ERR("select");
    if (new_r == 0)
		SERVER_ERR("Select: Time Out");
        
	_numberOfReadyFd = MAX(_numberOfReadyFd, new_r);
}


void	MasterServer::recvProcess()
{
	// Checking each socket for reading, starting from FD 3 because there should be nothing
	// to read from 0 (stdin), 1 (stdout) and 2 (stderr)
	for (int fd = 3; fd <= _maxFD && _numberOfReadyFd; ++fd)
	{
		if (FD_ISSET(fd, &_fdReader))
		{
			if (_fdServer.count(fd) == 1) // if fd is Server
				acceptClient(fd);
			else
			{
				char http_request[BUF_SIZE + 1];
				int valread;

				std::cout << "I'm receiving stuff from fd = " << fd << std::endl;

				valread = recv(fd, http_request, BUF_SIZE, 0);
				valread = '\0';
				std::cout << valread << std::endl;

				// parser->feed(http_request);

				if (valread == BUF_SIZE)
				{
					//Because of this case, you need to keep track of the parser used for a listen. Since you may use it again later to finish reading. Or, you must restart reading until you read it all.
					std::cout << "client read incomplete \n";
					// parser.parse();
					return;
				}
				else if (valread <= 0) // If receive nothing from clients
				{  
					//Close the socket and erase it from fd of clients
					int fdServ = findFdServer(fd); 
					std::cout << "BEFORE CLOSING: My client fd has: " << _fdMap[fdServ].second.size() << " elements.\n" << std::endl;
					close(fd);
					_fdMap[fdServ].second.erase(fd);
					std::cout << "Closing fd = " << fd << ". It belonged to " << fdServ << std::endl;
					std::cout << "My client fd has: " << _fdMap[fdServ].second.size() << " elements.\n" << std::endl;
				}
				// else if ((resp = parser.finishParse()) == NULL)
				// {
				// 	std::cout << "THIS SHOULD NOT HAPPEN EVER, SOMETHING IS VERY WRONG\n";
				// }
				else // send response
				{
					// resp->execute(this);
					// std::string finalResponsefake =
					// 	streamFunctionToString(&ResponseBuilder::print_response, resp);
					// std::cout
					// 	<< "finalResponsefake" << std::endl
					// 	<< finalResponsefake << std::endl;
					// send(fd, finalResponsefake.c_str(), finalResponsefake.size(), 0);

					std::string finalResponse = "HTTP/1.1 200 OK\nDate:Fri, 16 Mar 2020 17:21:12 GMT\nServer: my_server\nContent-Type: text/html;charset=UTF-8\nContent-Length: 1846\n\n<!DOCTYPE html>\n<html><h1>Hello world</h1></html>\n";
					std::cout << "A http response is sent\n" ;
					send(fd, finalResponse.c_str(), finalResponse.size(), 0);

					//Close the socket and erase it from client_fd of clients
					close (fd);
					int fdServ = findFdServer(fd); 
					_fdMap[fdServ].second.erase(fd);
					std::cout << "Closing " << fd << ". It belongs to " << fdServ << std::endl;
				}  
			}
			--_numberOfReadyFd;
		}
	}
}

void	MasterServer::acceptClient(int fdServer)
{
	sockaddr_in	sin;
	socklen_t	sin_len = 0;

	int	clientFD = accept(fdServer, (sockaddr *)&sin, &sin_len);
	if (clientFD == -1)
	{
		std::cerr << "Failed to accept a new connection\n";
		return; // ! do something more than that
	}
	std::cout 	<< "New client on socket #" << clientFD 
				<< ". This socket belongs to Server at socket #" << fdServer
				<< std::endl;
	// GrammarParser parser = GrammarParser(*_base_request_parser);
	std::string parser = "I'm a GrammarParser";
	_fdMap[fdServer].second[clientFD] = parser;
	std::cout << "My server socket at :" << fdServer << " has client socket: " << clientFD << std::endl;
}


int	MasterServer::findFdServer(int value)
{
	int fdServer = -1;

	// std::map<int, std::pair<OneServer*, std::map <int, GrammarParser> > >::iterator itFdMap;
	std::map<int, std::pair<OneServer*, std::map <int, std::string> > >::iterator itFdMap;

	for (itFdMap = _fdMap.begin(); itFdMap != _fdMap.end(); ++itFdMap)
	{
		// std::map<int, GrammarParser> clientMap;
		std::map<int, std::string> clientMap;
		clientMap = itFdMap->second.second;

		// std::map<int, GrammarParser>::iterator it_clientMap;
		std::map<int, std::string>::iterator it_clientMap;
		it_clientMap = clientMap.find(value);
		if (it_clientMap != clientMap.end())
		{
			fdServer = itFdMap->first;
			break; // to stop searching
		}
   }
   return fdServer;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */ 
