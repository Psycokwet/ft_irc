#ifndef IRCServer_HPP
#define IRCServer_HPP

#include "../../includes/ft_irc.hpp"
#include "../../includes/code.hpp"
#include "../Channel/Channel.hpp"
#include "../User/User.hpp"

#define TOO_MANY_ARGS ": Too many params"

class User;
class Channel;
class IRCServer;
class Client;

#define COMMAND_METHODS_PROTOTYPE bool (IRCServer::*)(t_client_ParsedCmd &, std::vector<t_clientCmd> &)
typedef std::map<std::string, COMMAND_METHODS_PROTOTYPE> t_commands_dictionary;
class IRCServer
{
public:
	IRCServer(std::string const &password);
	~IRCServer();

	void removeDisconnectUser(int fd);
	bool processCommand(t_client_ParsedCmd parsed_command, std::vector<t_clientCmd> &respQueue);
	int getVictim();
	User *one_user;

	static t_commands_dictionary _commandsDictionnary;
	static t_commands_dictionary initCommandsDictionnary();

private:
	std::map<int, User *> _users;				// Users list
	std::map<std::string, Channel *> _channels; // Channels list
	std::string const _serverPassword;
	int _fdToKill; // Fd of user killed by operater
	std::string const _prefix;

	// COMMANDS definitions
	bool ignore_command(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);  // please add needed arg as specified in "command_method"
	bool example_command(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue); // please add needed arg as specified in "command_method"

	bool execPASS(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);
	bool execNICK(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);
	bool execUSER(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);

	void removeUserFromAllChannels(User *user);
	void pushToQueue(int fd, std::string const &msg, std::vector<t_clientCmd> &respQueue) const;
	// void unknownCmd(t_client_ParsedCmd cmd, User *one_user, std::vector<t_clientCmd> &responseQueue) const;
	// std::string getResponseFromCode(User *user, int code, std::list<std::string> params) const;
};

#endif