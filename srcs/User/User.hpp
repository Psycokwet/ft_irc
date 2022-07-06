#ifndef USER_HPP
#define USER_HPP

class User;
class Channel;
#include "../../includes/ft_irc.hpp"
#include "../Channel/Channel.hpp"

class User
{
private:
	int _fd;						 // is the fd of client socket
	std::set<Channel *> _joinedList; // List of channels user has joined
	bool _passOK;					 // true if user provided required password by Server.
	bool _registered;				 // true if user provided name and required password by Server.
	std::string _nick;
	friend class IRCServer;

public:
	User(int fd);
	~User();

	int get_fd() const;
	bool getRegistered() const;
};

#endif