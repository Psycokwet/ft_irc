#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "MasterServer.hpp"

class Client;
#include "../../includes/ft_irc.hpp"

class Client
{
public:
	friend class IRCServer;
	~Client();
	Client();
	Client(int fd);
	bool receiveCommand(std::string &command);
	void sendResp(std::string const &resp);
	std::string getNick();

	bool
	always_true();
	bool always_false();
	bool is_not_connected();
	bool is_connected();
	bool is_registered();

private:
	int _fd; // is the fd of client socket
	// std::set<Channel *> _joinedList; // List of channels user has joined
	bool _passOK;	  // true if user provided required password by Server.
	bool _registered; // true if user provided name and required password by Server.
	std::string _nick;
	char _buffer[BUF_SIZE + 1];
	std::string _commandTemp;
};

#endif