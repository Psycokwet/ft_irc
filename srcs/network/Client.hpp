#ifndef CLIENT_HPP
#define CLIENT_HPP

class MasterServer;
#include "MasterServer.hpp"

class Client;
#include "../../includes/ft_irc.hpp"
#define UNDEFINED_NICK "*"
#include "../../includes/enumFactory.h"
#define E_MODE_CLIENT_ENUM(XX)                \
	XX(_MOD_NO_FLAGS, = (1u << 0))            \
	XX(_MOD_FLAG_ADMIN, = (1u << 1))          \
	XX(_MOD_FLAG_AWAY, = (1u << 2))           \
	XX(_MOD_FLAG_INVISIBLE, = (1u << 3))      \
	XX(_MOD_FLAG_WALLOPS, = (1u << 4))        \
	XX(_MOD_FLAG_RESTRICTED, = (1u << 5))     \
	XX(_MOD_FLAG_OPERATOR, = (1u << 6))       \
	XX(_MOD_FLAG_LOCAL_OPERATOR, = (1u << 7)) \
	XX(_MOD_FLAG_SERVER_NOTICES_RECEIVR, = (1u << 8))

/* _MOD_FLAG_ADMIN		 					  none - user is flagged as away;
** _MOD_FLAG_AWAY		 					  a - user is flagged as away;
** _MOD_FLAG_INVISIBLE		 				  i - marks a users as invisible;
** _MOD_FLAG_WALLOPS						  w - user receives wallops;
** _MOD_FLAG_RESTRICTED		 				  r - restricted user connection;
** _MOD_FLAG_OPERATOR		 				  o - operator flag;
** _MOD_FLAG_LOCAL_OPERATOR		 			  O - local operator flag;
** _MOD_FLAG_SERVER_NOTICES_RECEIVR		 	  s - marks a user for receipt of server notices.
*/

DECLARE_ENUM(e_mode_client, E_MODE_CLIENT_ENUM)
//				id		value			is settable by user
typedef std::map<char, std::pair<e_mode_client, bool> > t_char_client_mode_dictionary;

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
	std::string modeToString() const;

	void setRealName(std::string realName);
	std::string getNick() const;
	std::string getRealName() const;
	std::string getUserOnHost() const;
	e_mode_client getMode() const;
	bool addMode(e_mode_client mode);
	bool minusMode(e_mode_client mode);
	void setMode(e_mode_client mode);
	int getFd();
	bool always_true();
	bool always_false();
	bool is_not_connected();
	bool is_connected();
	bool is_registered();
	void validatedRegistration(std::vector<t_clientCmd> &respQueue, MasterServer *serv);

	bool operator==(const Client &rhs) const;
	// static
	static std::string modeToString(e_mode_client modes);
	static e_mode_client stringToMode(std::string s);
	static e_mode_client stringToClientSettableMode(std::string s);
	static t_char_client_mode_dictionary charClientModeDictionnary;
	static t_char_client_mode_dictionary initCharClientModeDictionnary();

	class unknownModeException : public std::exception
	{
	public:
		unknownModeException(void) {}
		virtual const char *what() const throw()
		{
			return "unknownModeException";
		}
	};

	class doubleSetModeException : public std::exception
	{
	public:
		doubleSetModeException(void) {}
		virtual const char *what() const throw()
		{
			return "doubleSetModeException";
		}
	};

private:
	int _fd; // is the fd of client socket
	// std::set<Channel *> _joinedList; // List of channels user has joined
	bool _passOK;	  // true if user provided required password by Server.
	bool _registered; // true if user provided name and required password by Server.
	std::string _nick;
	std::string _realName;
	std::string _userOnHost;
	e_mode_client _modes;
	char _buffer[BUF_SIZE + 1];
	std::string _commandTemp;
};

#endif