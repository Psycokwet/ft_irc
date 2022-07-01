#ifndef USER_HPP
#define USER_HPP

#include "../../includes/ft_irc.hpp"
#include "../Channel/Channel.hpp"

class User
{
private:
	int 				_fd;		 // is the fd of client socket
	std::set<Channel *> _joinedList; // List of channels user has joined
	bool 				_registered; // true if user provided name and required password by Server.
	std::string 		_nick;

public:
	User(int fd);
	~User();

	bool getRegistered() const;

	friend class IRCServer;

};

#endif