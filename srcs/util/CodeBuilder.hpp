#ifndef CODEBUILDER_HPP
#define CODEBUILDER_HPP

#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "../util/logger.hpp"

class Client;
class CodeBuilder;
class MasterServer;
#include "../network/MasterServer.hpp"
#include "../network/Client.hpp"
#define TOSTRING std::string (*)(std::string *, MasterServer *, Client *, Channel *)
typedef std::map<int, TOSTRING> t_code_dictionary;
// static use, singleton
class CodeBuilder
{

public:
	static std::string errorToString(int err, MasterServer *server, Client *client, std::string s = "", Channel *channel = NULL);
	static std::string errorToString(int err, MasterServer *server, Client *client, std::string *s, Channel *channel = NULL);

private:
	static t_code_dictionary _codeDictionnary;
	static t_code_dictionary initCodeDictionnary();

	static std::string errorCodeToString(int err);

	static std::string toStringRPL_CUSTOM(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringRPL_WELCOME(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringRPL_YOURHOST(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringRPL_CREATED(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringRPL_MYINFO(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringRPL_BOUNCE(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringERR_NEEDMOREPARAMS(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringERR_NICKNAMEINUSE(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringERR_NONICKNAMEGIVEN(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringERR_ALREADYREGISTRED(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringERR_NOSUCHNICK(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringERR_NORECIPIENT(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringERR_NOTEXTTOSEND(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringRPL_TOPIC(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringRPL_NAMREPLY(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringRPL_CHANNELMODEIS(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringRPL_ENDOFWHO(std::string *s, MasterServer *server, Client *client, Channel *channel);
	static std::string toStringRPL_WHOREPLY(std::string *s, MasterServer *server, Client *client, Channel *channel);

	static std::string toStringPLACEHOLDER(std::string *nick, MasterServer *server, Client *client, Channel *channel);

	CodeBuilder();
	CodeBuilder(CodeBuilder const &src);
	~CodeBuilder();
	CodeBuilder &operator=(CodeBuilder const &rhs);
};

#endif /* ***************************************************** CODEBUILDER_H */