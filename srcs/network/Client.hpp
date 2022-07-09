#ifndef CLIENT_HPP
#define CLIENT_HPP

class MasterServer;
#include "MasterServer.hpp"

class Client;
#include "../../includes/ft_irc.hpp"
#define UNDEFINED_NICK "*"

class Client
{
public:
	friend class MasterServer;
	friend class Channel;
	~Client();
	Client();
	Client(int fd);
	bool receiveCommand(std::string &command);
	void sendResp(std::string const &resp);
	std::string getNick();

	void setRealName(std::string realName);
	std::string getRealName();
	std::string getUserOnHost();
	int getFd();
	bool always_true();
	bool always_false();
	bool is_not_connected();
	bool is_connected();
	bool is_registered();
	void validatedRegistration(std::vector<t_clientCmd> &respQueue, MasterServer *serv);

	bool operator==(const Client &rhs) const;

private:
	int _fd; // is the fd of client socket
	// std::set<Channel *> _joinedList; // List of channels user has joined
	bool _passOK;	  // true if user provided required password by Server.
	bool _registered; // true if user provided name and required password by Server.
	std::string _nick;
	std::string _realName;
	std::string _userOnHost;
	char _buffer[BUF_SIZE + 1];
	std::string _commandTemp;
};

#endif
