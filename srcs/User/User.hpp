#ifndef USER_HPP
#define USER_HPP

#include "../../includes/ft_irc.hpp"
#include "../Channel/Channel.hpp"

class User
{

private:
	int _fd;						 // is the fd of client socket
	std::set<Channel *> _joinedList; // List of channels user has joined
	std::string _nick;

	bool _passOK;
	std::string _uname; // Username
	std::string _rname; // Real name

	bool _registered; // true if user provided name and required password by Server.

public:
	User(int fd);
	~User();

	bool getRegistered() const;

	void SetNick(std::string const &nick);
	void SetUsername(std::string const &uname);

	friend class IRCServer;
};

#endif