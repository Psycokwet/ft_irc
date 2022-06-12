#ifndef SERVER_HPP
#define SERVER_HPP

class Server;

#include <algorithm>
#include <sys/poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <vector>
#include <map>
#include <poll.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>

#include "utils.hpp"
#include "Client.hpp"

#define MAX_CONNECTIONS 1000

class Server
{
    int _run;
    int _sock;

    const std::string _host;
    const std::string  _port;
    const std::string _password;

    std::vector<pollfd>			_pollfds;

    std::map<int, Client *>		_clients;

    typedef std::vector<pollfd>::iterator pollfds_iterator;







    public:

    Server(const std::string &port, const std::string &password);
    ~Server();

    void start();


    int newSocket();

    void ClientConnect();
    void ClientDisconnect(int fd);


};







#endif