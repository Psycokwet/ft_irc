#ifndef IRCServer_HPP
#define IRCServer_HPP

#include "../../includes/ft_irc.hpp"
#include "../network/Client.hpp"
#include "../util/CodeBuilder.hpp"
#include "../../includes/code.hpp"
// #include "../Channel/Channel.hpp"
// #include "../User/User.hpp"

#define TOO_MANY_ARGS ": Too many params"
#define HOST "ourirc.42.paris.fr"

// class Channel;
class CodeBuilder;
class Client;
class IRCServer;

typedef std::pair<Client *, lazyParsedType *> t_client_ParsedCmd; // it: fd client, lazyParsedType: parsed command

#define COMMAND_METHODS_PROTOTYPE bool (IRCServer::*)(std::string base, t_client_ParsedCmd &, std::vector<t_clientCmd> &)
#define CHECK_COMMAND_VALIDITY_METHODS_PROTOTYPE bool (Client::*)()
typedef std::map<std::string, std::pair<CHECK_COMMAND_VALIDITY_METHODS_PROTOTYPE, COMMAND_METHODS_PROTOTYPE> > t_commands_dictionary;
class IRCServer
{
public:
	IRCServer(std::string const &password);
	~IRCServer();

	std::string getHost() const;
	// void removeDisconnectUser(int fd);
	bool processCommand(std::string base, t_client_ParsedCmd parsed_command, std::vector<t_clientCmd> &respQueue);
	// int getVictim();

	static t_commands_dictionary _commandsDictionnary;
	static t_commands_dictionary initCommandsDictionnary();

private:
	// std::map<int, User *> _users;				// Users list
	// std::map<std::string, Channel *> _channels; // Channels list
	std::string const _serverPassword;
	// int 								_fdToKill; // Fd of user killed by operater
	std::string const _prefix;

	// COMMANDS definitions
	bool ignore_command(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);	 // please add needed arg as specified in "command_method"
	bool example_command(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue); // please add needed arg as specified in "command_method"

	bool execPASS(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);
	bool execNICK(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);
	bool execUSER(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);

	// void removeUserFromAllChannels(User *user);
	void pushToQueue(int fd, std::string const &msg, std::vector<t_clientCmd> &respQueue) const;
	// void unknownCmd(t_client_ParsedCmd cmd, User *one_user, std::vector<t_clientCmd> &responseQueue) const;
	// std::string getResponseFromCode(User *user, int code, std::list<std::string> params) const;
};

#endif