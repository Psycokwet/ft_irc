#ifndef MASTERSERVER_HPP
#define MASTERSERVER_HPP

#include "../../includes/ft_irc.hpp"
#include "Client.hpp"
#include "../IrcServer/IRCServer.hpp"
#include "../util/containerTo.hpp"
#define CMD_SEP "\r\n"

class Client;

class MasterServer
{
public:
	MasterServer(int port, std::string const &password, IRCServer &irc);
	MasterServer &operator=(const MasterServer &rhs);
	~MasterServer();

	std::ostream &print_client_map(std::ostream &o) const;

	int build();
	void run();

	// class AnError : public std::exception
	// {
	// 	public:
	// 		virtual const char *what() const throw()
	// 		{
	// 			return "ERROR: ";
	// 		}
	// };

private:
	int _fdServer; // Server's socket
	std::map<int, Client *> _clients;
	int _maxFD;		  // Current highest client FD
	fd_set _fdReader; // Structure to select client FD for reading
	IRCServer &_ircServer;
	int _port;
	std::string const _password;

	int setFDForReading();
	void recvProcess(int totalFf, std::vector<t_clientCmd> &resQueue, std::set<int> &disconnectList);
	void acceptClient(int fdServer);
	void removeClient(int fdClient);
};

#endif /*...................MasterServer...............*/