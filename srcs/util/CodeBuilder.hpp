#ifndef CODEBUILDER_HPP
#define CODEBUILDER_HPP

#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "../util/logger.hpp"

class Client;
class CodeBuilder;
class IRCServer;
#include "../network/Client.hpp"
#include "../IrcServer/IRCServer.hpp"
#define TOSTRING std::string (*)(std::string *, IRCServer *, Client *)
typedef std::map<int, TOSTRING> t_code_dictionary;
// static use, singleton
class CodeBuilder
{

public:
	static std::string errorToString(int err, IRCServer *server = NULL, Client *client = NULL, std::string *s = NULL);

private:
	static t_code_dictionary _codeDictionnary;
	static t_code_dictionary initCodeDictionnary();

	static std::string errorCodeToString(int err);

	static std::string toStringRPL_CUSTOM(std::string *s, IRCServer *server, Client *client);
	static std::string toStringRPL_WELCOME(std::string *s, IRCServer *server, Client *client);
	static std::string toStringRPL_YOURHOST(std::string *s, IRCServer *server, Client *client);
	static std::string toStringRPL_CREATED(std::string *s, IRCServer *server, Client *client);
	static std::string toStringRPL_MYINFO(std::string *s, IRCServer *server, Client *client);
	static std::string toStringRPL_BOUNCE(std::string *s, IRCServer *server, Client *client);
	static std::string toStringERR_NEEDMOREPARAMS(std::string *s, IRCServer *server, Client *client);
	static std::string toStringERR_NICKNAMEINUSE(std::string *s, IRCServer *server, Client *client);
	static std::string toStringERR_NONICKNAMEGIVEN(std::string *s, IRCServer *server, Client *client);
	static std::string toStringERR_ALREADYREGISTRED(std::string *s, IRCServer *server, Client *client);

	static std::string toStringPLACEHOLDER(std::string *nick, IRCServer *server, Client *client);

	CodeBuilder();
	CodeBuilder(CodeBuilder const &src);
	~CodeBuilder();
	CodeBuilder &operator=(CodeBuilder const &rhs);
};

#endif /* ***************************************************** CODEBUILDER_H */