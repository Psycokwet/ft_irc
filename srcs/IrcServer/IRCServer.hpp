#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP

#include <iostream>
#include <string>
#include <map>

#include "../Channel/Channel.hpp"
#include "../User/User.hpp"
#include "../../includes/ft_irc.hpp"
#include "../../includes/code.hpp"

#include "../../includes/ft_irc.hpp"
#include "../Channel/Channel.hpp"
#include "../User/User.hpp"

class User;
class Channel;

class IRCServer
{

public:
	IRCServer(std::string const &password);
	IRCServer(IRCServer const &src);
	virtual ~IRCServer();

	IRCServer &operator=(IRCServer const &rhs);

	void removeDisconnectUser(int fd);
	bool processCommand(t_client_ParsedCmd command, std::vector<t_clientCmd> &respQueue);
	int getVictim();

	User *getUserByNick(std::string const &nick) const;
	Channel *getChannelByName(std::string const &name) const;

private:
	std::map<int, User *> _users;				// Users list
	std::map<std::string, Channel *> _channels; // Channels list
	std::string const _serverPassword;
	std::string const _prefix; // server prefix

	int _fdToKill; // Fd of user killed by operater

	// USERS //

	void leave(User *user, Channel *chan); // leave channel
	void remove(User *user);			   // remove all channel
	void welcome(User *user, std::vector<t_clientCmd> &respQueue);

	// CHANNEL //

	Channel *newChannel(std::string const &name, User *creat);
	std::set<User *> getCommonUser(User *user) const;
	Channel *getChannelName(std::string const &name) const;

	// command execute

	void PASS(t_client_ParsedCmd command, std::vector<t_clientCmd> &respQueue);

	// command

	std::string getResponseCode(User *user, int code, std::string param[]) const;
};

std::ostream &operator<<(std::ostream &o, IRCServer const &i);

#endif /* ******************************************************* IRCSERVER_H */
