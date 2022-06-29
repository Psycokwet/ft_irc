#ifndef IRCServer_HPP
#define IRCServer_HPP

#include "../../includes/ft_irc.hpp"
#include "../Channel/Channel.hpp"
#include "../User/User.hpp"

class User;
class Channel;
class IRCServer;

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

	static t_commands_dictionary _commandsDictionnary;
	static t_commands_dictionary initCommandsDictionnary();

private:
	std::map<int, User *> _users;				// Users list
	std::map<std::string, Channel *> _channels; // Channels list
	std::string const _serverPassword;
	int _fdToKill; // Fd of user killed by operater
	std::vector<std::string> _params;

	// command execute
	void PASS(t_client_ParsedCmd command, std::vector<t_clientCmd> &respQueue);

	// COMMANDS definitions
	bool ignore_command(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);  // please add needed arg as specified in "command_method"
	bool example_command(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue); // please add needed arg as specified in "command_method"
	bool execNICK(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue); 

	void removeUserFromAllChannels(User *user);
};

#endif