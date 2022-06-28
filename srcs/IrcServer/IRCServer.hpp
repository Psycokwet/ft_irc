#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP

#include <iostream>
#include <string>

#include "../Channel/Channel.hpp"
#include "../User/User.hpp"
#include "../../includes/ft_irc.hpp"
#include "../../includes/code.hpp"

class IRCServer
{

public:
	IRCServer(std::string const &password);
	IRCServer(IRCServer const &src);
	virtual ~IRCServer();

	IRCServer &operator=(IRCServer const &rhs);

	User *getUserByNick(std::string const &nick) const;
	Channel *getChannelByName(std::string const &name) const;

private:
	std::map<int, User *> _User_list;				// Users list
	std::map<std::string, Channel *> _channel_list; // Channels list

	int _killing; // fd users killing by operator

	// USERS //

	void leave(User *user, Channel *chan); // leave channel
	void remove(User *user);			   // remove all channel
	void welcome();

	Channel *newChannel(std::string const &name, User *creat);
	std::set<User *> getCommonUser(User *user) const;
	Channel *getChannelName(std::string const &name) const;

	// command

	void PASS(Command const &cmd, std::vector<t_clientCmd> &responseQueue);
};

std::ostream &operator<<(std::ostream &o, IRCServer const &i);

#endif /* ******************************************************* IRCSERVER_H */
