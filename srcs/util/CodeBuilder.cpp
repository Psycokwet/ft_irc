#include "CodeBuilder.hpp"

/*
** ------------------------------- STATIC --------------------------------
*/
t_code_dictionary CodeBuilder::initCodeDictionnary()
{
	t_code_dictionary map;
	map[RPL_CUSTOM] = &CodeBuilder::toStringRPL_CUSTOM;
	map[RPL_WELCOME] = &CodeBuilder::toStringRPL_WELCOME;
	map[RPL_YOURHOST] = &CodeBuilder::toStringRPL_YOURHOST;
	map[RPL_CREATED] = &CodeBuilder::toStringRPL_CREATED;
	map[RPL_MYINFO] = &CodeBuilder::toStringRPL_MYINFO;
	map[RPL_BOUNCE] = &CodeBuilder::toStringRPL_BOUNCE;
	// 200
	map[RPL_TRACELINK] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TRACECONNECTING] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TRACEHANDSHAKE] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TRACEUNKNOWN] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TRACEOPERATOR] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TRACEUSER] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TRACESERVER] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TRACESERVICE] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TRACENEWTYPE] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TRACECLASS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TRACERECONNECT] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_STATSLINKINFO] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_STATSCOMMANDS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFSTATS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_UMODEIS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_SERVLIST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_SERVLISTEND] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_STATSUPTIME] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_STATSOLINE] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_LUSERCLIENT] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_LUSEROP] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_LUSERUNKNOWN] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_LUSERCHANNELS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_LUSERME] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ADMINME] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ADMINLOC1] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ADMINLOC2] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ADMINEMAIL] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TRACELOG] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TRACEEND] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TRYAGAIN] = &CodeBuilder::toStringPLACEHOLDER;
	// 300
	map[RPL_AWAY] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_USERHOST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ISON] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_UNAWAY] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_NOWAWAY] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_WHOISUSER] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_WHOISSERVER] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_WHOISOPERATOR] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_WHOWASUSER] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFWHO] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_WHOISIDLE] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFWHOIS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_WHOISCHANNELS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_LISTSTART] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_LIST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_LISTEND] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_CHANNELMODEIS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_UNIQOPIS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_NOTOPIC] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TOPIC] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_INVITING] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_SUMMONING] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_INVITELIST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFINVITELIST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_EXCEPTLIST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFEXCEPTLIST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_VERSION] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_WHOREPLY] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_NAMREPLY] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_LINKS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFLINKS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFNAMES] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_BANLIST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFBANLIST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFWHOWAS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_INFO] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_MOTD] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFINFO] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_MOTDSTART] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFMOTD] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_YOUREOPER] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_REHASHING] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_YOURESERVICE] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TIME] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_USERSSTART] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_USERS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFUSERS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_NOUSERS] = &CodeBuilder::toStringPLACEHOLDER;
	// 400
	map[ERR_NOSUCHNICK] = &CodeBuilder::toStringERR_NOSUCHNICK;
	map[ERR_NOSUCHSERVER] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NOSUCHCHANNEL] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_CANNOTSENDTOCHAN] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_TOOMANYCHANNELS] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_WASNOSUCHNICK] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_TOOMANYTARGETS] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NOSUCHSERVICE] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NOORIGIN] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NORECIPIENT] = &CodeBuilder::toStringERR_NORECIPIENT;
	map[ERR_NOTEXTTOSEND] = &CodeBuilder::toStringERR_NOTEXTTOSEND;
	map[ERR_NOTOPLEVEL] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_WILDTOPLEVEL] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_BADMASK] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_UNKNOWNCOMMAND] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NOMOTD] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NOADMININFO] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_FILEERROR] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NONICKNAMEGIVEN] = &CodeBuilder::toStringERR_NONICKNAMEGIVEN;
	map[ERR_ERRONEUSNICKNAME] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NICKNAMEINUSE] = &CodeBuilder::toStringERR_NICKNAMEINUSE;
	map[ERR_NICKCOLLISION] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_UNAVAILRESOURCE] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_USERNOTINCHANNEL] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NOTONCHANNEL] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_USERONCHANNEL] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NOLOGIN] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_SUMMONDISABLED] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_USERSDISABLED] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NOTREGISTERED] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NEEDMOREPARAMS] = &CodeBuilder::toStringERR_NEEDMOREPARAMS;
	map[ERR_ALREADYREGISTRED] = &CodeBuilder::toStringERR_ALREADYREGISTRED;
	map[ERR_NOPERMFORHOST] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_PASSWDMISMATCH] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_YOUREBANNEDCREEP] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_YOUWILLBEBANNED] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_KEYSET] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_CHANNELISFULL] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_UNKNOWNMODE] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_INVITEONLYCHAN] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_BANNEDFROMCHAN] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_BADCHANNELKEY] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_BADCHANMASK] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NOCHANMODES] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_BANLISTFULL] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NOPRIVILEGES] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_CHANOPRIVSNEEDED] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_CANTKILLSERVER] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_RESTRICTED] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_UNIQOPPRIVSNEEDED] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NOOPERHOST] = &CodeBuilder::toStringPLACEHOLDER;
	// 500
	map[ERR_UMODEUNKNOWNFLAG] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_USERSDONTMATCH] = &CodeBuilder::toStringPLACEHOLDER;

	return map;
}

t_code_dictionary CodeBuilder::_codeDictionnary = CodeBuilder::initCodeDictionnary();

/*
** --------------------------------- STATIC METHODS ----------------------------------
*/

std::string CodeBuilder::errorToString(int err, MasterServer *server, Client *client, std::string *s)
{
	std::string tmp = ":No registered error code found";
	std::string string_code = "042";
	if (_codeDictionnary.find(err) != _codeDictionnary.end())
	{
		tmp = _codeDictionnary[err](s, server, client);
		string_code = errorCodeToString(err);
	}

	std::stringstream ss;
	print_cont(ss, stringToList(tmp, '\n'), END_OF_COMMAND, ":" + server->getHost() + " " + string_code + " * ");
	return ss.str();

	// 	return server->getHost() + " " + errorCodeToString(err) + " " + client->getUserOnHost() + " " + _codeDictionnary[err](s, server, client);
	// return server->getHost() + " 042 " + client->getUserOnHost() + ":No registered error code found";
}
std::string CodeBuilder::errorCodeToString(int err)
{
	std::stringstream ss;
	ss << std::setw(3) << std::setfill('0') << err;
	return ss.str();
}

/*
** --------------------------------- DICTIONARY ENTRIES ----------------------------------
*/

std::string CodeBuilder::toStringRPL_CUSTOM(std::string *s, MasterServer *server, Client *client)
{
	(void)s;
	(void)server;
	(void)client;
	return ":Hmm, hello there ! Howdy !";
}

std::string CodeBuilder::toStringRPL_WELCOME(std::string *s, MasterServer *server, Client *client)
{
	(void)s;
	return ":Welcome to the Internet Relay Network " + server->getFullClientID(client);
}
std::string CodeBuilder::toStringRPL_YOURHOST(std::string *s, MasterServer *server, Client *client)
{
	(void)s;
	(void)server;
	(void)client;
	return ":Your host is " + server->getServerName() + ", running version " + server->getServerVersion();
}
std::string CodeBuilder::toStringRPL_CREATED(std::string *s, MasterServer *server, Client *client)
{
	(void)s;
	(void)server;
	(void)client;
	return ":This server was created " + server->getCreationDate();
}
std::string CodeBuilder::toStringRPL_MYINFO(std::string *s, MasterServer *server, Client *client)
{
	(void)s;
	(void)server;
	(void)client;
	return ":" + server->getServerName() + " " + server->getServerVersion() + " " + server->getAvailableUserModes() + " :" + server->getAvailableChannelModes();
}
std::string CodeBuilder::toStringRPL_BOUNCE(std::string *s, MasterServer *server, Client *client)
{
	(void)s;
	(void)server;
	(void)client;
	return ":Try server any you like, really lol, port look it up :p";
}

std::string CodeBuilder::toStringERR_NEEDMOREPARAMS(std::string *command_name, MasterServer *server, Client *client)
{
	(void)server;
	(void)client;
	return (*command_name) + ":Not enough parameters";
}
std::string CodeBuilder::toStringERR_NONICKNAMEGIVEN(std::string *s, MasterServer *server, Client *client)
{
	(void)server;
	(void)client;
	(void)s;
	return ":No nickname given";
}

std::string CodeBuilder::toStringERR_NICKNAMEINUSE(std::string *nick, MasterServer *server, Client *client)
{
	(void)server;
	(void)client;
	return (*nick) + " :Nickname is already in use";
}
// :ourirc.42.paris.fr 433  user42 :Nickname is already in use\r\n
// :ft-irc.42.fr 433 * user42 :Nickname is already in use\r\n
std::string CodeBuilder::toStringERR_ALREADYREGISTRED(std::string *s, MasterServer *server, Client *client)
{
	(void)server;
	(void)s;
	(void)client;
	return ":Unauthorized command (already registered)";
}

std::string CodeBuilder::toStringERR_NOSUCHNICK(std::string *destNick, MasterServer *server, Client *client)
{
	(void)server;
	(void)client;
	return *destNick + " :No such nick/channel";
}
std::string CodeBuilder::toStringERR_NORECIPIENT(std::string *command, MasterServer *server, Client *client)
{
	(void)server;
	(void)client;
	return ":No recipient given (" + *command + ")";
}
std::string CodeBuilder::toStringERR_NOTEXTTOSEND(std::string *s, MasterServer *server, Client *client)
{
	(void)server;
	(void)client;
	(void)s;
	return ":No text to send";
}

std::string CodeBuilder::toStringPLACEHOLDER(std::string *s, MasterServer *server, Client *client)
{
	(void)server;
	(void)client;
	(void)s;
	return ":I AM A PLACEHOLDER ";
}

/* ************************************************************************** */