#ifndef MASTERSERVER_HPP
#define MASTERSERVER_HPP

#include "../../includes/ft_irc.hpp"
class CodeBuilder;
class Client;
class Channel;
#include "Client.hpp"
#include "Channel.hpp"
#include "../util/CodeBuilder.hpp"
#include "../util/deleteContainers.hpp"
#include "../util/containerTo.hpp"
#include "../../includes/code.hpp"

#include "../../includes/enumFactory.h"
#define E_MODE_CLIENT_ENUM(XX)                \
	XX(_MOD_NO_FLAGS, = (1u << 0))            \
	XX(_MOD_FLAG_ADMIN, = (1u << 1))          \
	XX(_MOD_FLAG_AWAY, = (1u << 2))           \
	XX(_MOD_FLAG_INVISIBLE, = (1u << 3))      \
	XX(_MOD_FLAG_RESTRICTED, = (1u << 4))     \
	XX(_MOD_FLAG_OPERATOR, = (1u << 5))       \
	XX(_MOD_FLAG_LOCAL_OPERATOR, = (1u << 6)) \
	XX(_MOD_FLAG_SERVER_NOTICES_RECEIVR, = (1u << 7))

/* _MOD_FLAG_ADMIN		 					  a - user is flagged as away;
** _MOD_FLAG_AWAY		 					  i - marks a users as invisible;
** _MOD_FLAG_INVISIBLE						  w - user receives wallops;
** _MOD_FLAG_RESTRICTED		 				  r - restricted user connection;
** _MOD_FLAG_OPERATOR		 				  o - operator flag;
** _MOD_FLAG_LOCAL_OPERATOR		 			  O - local operator flag;
** _MOD_FLAG_SERVER_NOTICES_RECEIVR		 	  s - marks a user for receipt of server notices.
*/

DECLARE_ENUM(e_mode_client, E_MODE_CLIENT_ENUM)

typedef std::pair<Client *, lazyParsedType *> t_client_ParsedCmd; // it: fd client, lazyParsedType: parsed command

#define COMMAND_METHODS_PROTOTYPE bool (MasterServer::*)(std::string base, t_client_ParsedCmd &, std::vector<t_clientCmd> &)
#define CHECK_COMMAND_VALIDITY_METHODS_PROTOTYPE bool (Client::*)()
typedef std::map<std::string, std::pair<CHECK_COMMAND_VALIDITY_METHODS_PROTOTYPE, COMMAND_METHODS_PROTOTYPE> > t_commands_dictionary;
typedef std::map<char, int> t_char_client_mode_dictionary;

class MasterServer
{
public:
	friend class Client;
	friend class Channel;
	MasterServer(int port, std::string const &password);
	MasterServer &operator=(const MasterServer &rhs);
	~MasterServer();

	std::ostream &print_client_map(std::ostream &o) const;

	int build();
	void run();

	Client *findClientWithNick(std::string new_nick);
	Channel *findChanneWithName(std::string name);
	Channel *createChannel(std::string name);

	std::string getHost() const;
	std::string getServerName() const;
	std::string getServerVersion() const;
	std::string getCreationDate() const;
	std::string getAvailableUserModes() const;
	std::string getAvailableChannelModes() const;

	std::string getFullClientID(Client *c) const;

	bool processCommand(std::string base, t_client_ParsedCmd parsed_command, std::vector<t_clientCmd> &respQueue);

	static t_commands_dictionary _commandsDictionnary;
	static t_commands_dictionary initCommandsDictionnary();
	static t_char_client_mode_dictionary _charClientModeDictionnary;
	static t_char_client_mode_dictionary initCharClientModeDictionnary();

private:
	int _fdServer; // Server's socket
	std::map<int, Client *> _clients;
	std::map<std::string, Channel *> _channels;
	int _maxFD;		  // Current highest client FD
	fd_set _fdReader; // Structure to select client FD for reading
	int _port;
	std::string const _password;

	int setFDForReading();
	void recvProcess(int totalFf, std::vector<t_clientCmd> &resQueue, std::set<int> &disconnectList);
	void acceptClient(int fdServer);
	void removeClient(int fdClient);

	void pushToQueue(int fd, std::string const &msg, std::vector<t_clientCmd> &respQueue) const;

	// COMMANDS definitions
	bool ignore_command(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);	 // please add needed arg as specified in "command_method"
	bool example_command(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue); // please add needed arg as specified in "command_method"

	bool execPASS(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);
	bool execNICK(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);
	bool execUSER(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);
	bool execPRIVMSG(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);
	bool execJOIN(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);

	bool execMODE_CHANNEL(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);
	bool execMODE_CLIENT(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);
	bool execMODE(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);

	bool execWHO(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);
	
	bool execPING(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue);
};

#endif /*...................MasterServer...............*/