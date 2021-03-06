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
	map[RPL_UMODEIS] = &CodeBuilder::toStringRPL_UMODEIS;
	map[RPL_SERVLIST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_SERVLISTEND] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_STATSUPTIME] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_STATSOLINE] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_LUSERCLIENT] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_LUSEROP] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_LUSERUNKNOWN] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_LUSERCHANNELS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_LUSERME] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ADMINME] = &CodeBuilder::toStringRPL_ADMINME;
	map[RPL_ADMINLOC1] = &CodeBuilder::toStringRPL_ADMINLOC1;
	map[RPL_ADMINLOC2] = &CodeBuilder::toStringRPL_ADMINLOC2;
	map[RPL_ADMINEMAIL] = &CodeBuilder::toStringRPL_ADMINEMAIL;
	map[RPL_TRACELOG] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TRACEEND] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TRYAGAIN] = &CodeBuilder::toStringPLACEHOLDER;
	// 300
	map[RPL_AWAY] = &CodeBuilder::toStringRPL_AWAY;
	map[RPL_USERHOST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ISON] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_UNAWAY] = &CodeBuilder::toStringRPL_UNAWAY;
	map[RPL_NOWAWAY] = &CodeBuilder::toStringRPL_NOWAWAY;
	map[RPL_WHOISUSER] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_WHOISSERVER] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_WHOISOPERATOR] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_WHOWASUSER] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFWHO] = &CodeBuilder::toStringRPL_ENDOFWHO;
	map[RPL_WHOISIDLE] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFWHOIS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_WHOISCHANNELS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_LISTSTART] = &CodeBuilder::toStringRPL_LISTSTART;
	map[RPL_LIST] = &CodeBuilder::toStringRPL_LIST;
	map[RPL_LISTEND] = &CodeBuilder::toStringRPL_LISTEND;
	map[RPL_CHANNELMODEIS] = &CodeBuilder::toStringRPL_CHANNELMODEIS;
	map[RPL_UNIQOPIS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_NOTOPIC] = &CodeBuilder::toStringRPL_NOTOPIC;
	map[RPL_TOPIC] = &CodeBuilder::toStringRPL_TOPIC;
	map[RPL_INVITING] = &CodeBuilder::toStringRPL_INVITING;
	map[RPL_SUMMONING] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_INVITELIST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFINVITELIST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_EXCEPTLIST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFEXCEPTLIST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_VERSION] = &CodeBuilder::toStringRPL_VERSION;
	map[RPL_WHOREPLY] = &CodeBuilder::toStringRPL_WHOREPLY;
	map[RPL_NAMREPLY] = &CodeBuilder::toStringRPL_NAMREPLY;
	map[RPL_LINKS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFLINKS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFNAMES] = &CodeBuilder::toStringRPL_ENDOFNAMES;
	map[RPL_BANLIST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFBANLIST] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFWHOWAS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_INFO] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_MOTD] = &CodeBuilder::toStringRPL_MOTD;
	map[RPL_ENDOFINFO] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_MOTDSTART] = &CodeBuilder::toStringRPL_MOTDSTART;
	map[RPL_ENDOFMOTD] = &CodeBuilder::toStringRPL_ENDOFMOTD;
	map[RPL_YOUREOPER] = &CodeBuilder::toStringRPL_YOUREOPER;
	map[RPL_REHASHING] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_YOURESERVICE] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_TIME] = &CodeBuilder::toStringRPL_TIME;
	map[RPL_USERSSTART] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_USERS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_ENDOFUSERS] = &CodeBuilder::toStringPLACEHOLDER;
	map[RPL_NOUSERS] = &CodeBuilder::toStringPLACEHOLDER;
	// 400
	map[ERR_NOSUCHNICK] = &CodeBuilder::toStringERR_NOSUCHNICK;
	map[ERR_NOSUCHSERVER] = &CodeBuilder::toStringERR_NOSUCHSERVER;
	map[ERR_NOSUCHCHANNEL] = &CodeBuilder::toStringERR_NOSUCHCHANNEL;
	map[ERR_CANNOTSENDTOCHAN] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_TOOMANYCHANNELS] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_WASNOSUCHNICK] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_TOOMANYTARGETS] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NOSUCHSERVICE] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NOORIGIN] = &CodeBuilder::toStringERR_NOORIGIN;
	map[ERR_NORECIPIENT] = &CodeBuilder::toStringERR_NORECIPIENT;
	map[ERR_NOTEXTTOSEND] = &CodeBuilder::toStringERR_NOTEXTTOSEND;
	map[ERR_NOTOPLEVEL] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_WILDTOPLEVEL] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_BADMASK] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_UNKNOWNCOMMAND] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NOMOTD] = &CodeBuilder::toStringERR_NOMOTD;
	map[ERR_NOADMININFO] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_FILEERROR] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NONICKNAMEGIVEN] = &CodeBuilder::toStringERR_NONICKNAMEGIVEN;
	map[ERR_ERRONEUSNICKNAME] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NICKNAMEINUSE] = &CodeBuilder::toStringERR_NICKNAMEINUSE;
	map[ERR_NICKCOLLISION] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_UNAVAILRESOURCE] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_USERNOTINCHANNEL] = &CodeBuilder::toStringERR_USERNOTINCHANNEL;
	map[ERR_NOTONCHANNEL] = &CodeBuilder::toStringERR_NOTONCHANNEL;
	map[ERR_USERONCHANNEL] = &CodeBuilder::toStringERR_USERONCHANNEL;
	map[ERR_NOLOGIN] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_SUMMONDISABLED] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_USERSDISABLED] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NOTREGISTERED] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NEEDMOREPARAMS] = &CodeBuilder::toStringERR_NEEDMOREPARAMS;
	map[ERR_ALREADYREGISTRED] = &CodeBuilder::toStringERR_ALREADYREGISTRED;
	map[ERR_NOPERMFORHOST] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_PASSWDMISMATCH] = &CodeBuilder::toStringERR_PASSWDMISMATCH;
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
	map[ERR_NOPRIVILEGES] = &CodeBuilder::toStringERR_NOPRIVILEGES;
	map[ERR_CHANOPRIVSNEEDED] = &CodeBuilder::toStringERR_CHANOPRIVSNEEDED;
	map[ERR_CANTKILLSERVER] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_RESTRICTED] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_UNIQOPPRIVSNEEDED] = &CodeBuilder::toStringPLACEHOLDER;
	map[ERR_NOOPERHOST] = &CodeBuilder::toStringPLACEHOLDER;
	// 500
	map[ERR_UMODEUNKNOWNFLAG] = &CodeBuilder::toStringERR_UMODEUNKNOWNFLAG;
	map[ERR_USERSDONTMATCH] = &CodeBuilder::toStringERR_USERSDONTMATCH;

	return map;
}

t_code_dictionary CodeBuilder::_codeDictionnary = CodeBuilder::initCodeDictionnary();

/*
** --------------------------------- STATIC METHODS ----------------------------------
*/

std::string CodeBuilder::errorToString(int err, MasterServer *server, Client *client, std::string s, Channel *channel)
{
	return CodeBuilder::errorToString(err, server, client, &s, channel);
}

std::string CodeBuilder::errorToString(int err, MasterServer *server, Client *client, std::string *s, Channel *channel)
{
	std::string tmp = ":No registered error code found";
	std::string string_code = "042";
	if (_codeDictionnary.find(err) != _codeDictionnary.end())
	{
		tmp = _codeDictionnary[err](s, server, client, channel);
		string_code = errorCodeToString(err);
	}

	std::stringstream ss;
	print_cont(ss, stringToList(tmp, '\n'), END_OF_COMMAND, ":" + server->getHost() + " " + string_code + " " + client->getNick() + " ");
	return ss.str();
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

std::string CodeBuilder::toStringRPL_CUSTOM(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)s;
	(void)server;
	(void)client;
	(void)channel;
	return ":Hmm, hello there ! Howdy !";
}

std::string CodeBuilder::toStringRPL_WELCOME(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)s;
	(void)channel;

	return ":Welcome to the Internet Relay Network " + server->getFullClientID(client);
}
std::string CodeBuilder::toStringRPL_YOURHOST(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)s;
	(void)server;
	(void)client;
	(void)channel;

	return ":Your host is " + server->getServerName() + ", running version " + server->getServerVersion();
}

std::string CodeBuilder::toStringRPL_VERSION(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)s;
	(void)server;
	(void)client;
	(void)channel;

	return "NOTICE: " + server->getServerName() + " :" + server->getServerVersion();
}

std::string CodeBuilder::toStringRPL_CREATED(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)s;
	(void)server;
	(void)client;
	(void)channel;

	return ":This server was created " + server->getCreationDate();
}
std::string CodeBuilder::toStringRPL_MYINFO(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)s;
	(void)server;
	(void)client;
	(void)channel;

	return ":" + server->getServerName() + " " + server->getServerVersion() + " " + server->getAvailableUserModes() + " :" + server->getAvailableChannelModes();
}
std::string CodeBuilder::toStringRPL_BOUNCE(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)s;
	(void)server;
	(void)client;
	(void)channel;

	return ":Try server any you like, really lol, port look it up :p";
}

std::string CodeBuilder::toStringERR_NEEDMOREPARAMS(std::string *command_name, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;

	return (*command_name) + " :Not enough parameters";
}
std::string CodeBuilder::toStringERR_NONICKNAMEGIVEN(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;

	return ":No nickname given";
}

std::string CodeBuilder::toStringERR_NICKNAMEINUSE(std::string *nick, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;

	return (*nick) + " :Nickname is already in use";
}

std::string CodeBuilder::toStringERR_ALREADYREGISTRED(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)s;
	(void)client;
	(void)channel;

	return ":Unauthorized command (already registered)";
}
std::string CodeBuilder::toStringERR_PASSWDMISMATCH(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)s;
	(void)client;
	(void)channel;

	return ":Password incorrect";
}

std::string CodeBuilder::toStringERR_NOSUCHNICK(std::string *destNick, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;

	return *destNick + " :No such nick/channel";
}
std::string CodeBuilder::toStringERR_NORECIPIENT(std::string *command, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;

	return ":No recipient given (" + *command + ")";
}
std::string CodeBuilder::toStringERR_NOTEXTTOSEND(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;

	return ":No text to send";
}

std::string CodeBuilder::toStringRPL_TOPIC(std::string *s, MasterServer *server, Client *client, Channel *channel)
{

	(void)server;
	(void)client;
	(void)channel;
	(void)s;

	std::string tmp = " :";
	if (channel)
		tmp = channel->getName() + tmp + channel->getTopic();
	return tmp;
	//<channel> : <topic>
}
std::string CodeBuilder::toStringRPL_NAMREPLY(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;

	std::string tmp = " :";
	if (channel)
		tmp = channel->getName() + tmp + channel->clientListToString(false);
	return "= " + tmp;
	//	= #pwat :user42_ @user42__
	//	"@" is used for secret channels, "*" for private channels,
	//	and "=" for others (public channels).
}

std::string CodeBuilder::toStringRPL_YOUREOPER(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;

	return ":You are now an IRC operator";
}
std::string CodeBuilder::toStringRPL_CHANNELMODEIS(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;
	std::string tmp = " :";
	if (channel)
		tmp = channel->getName() + tmp + channel->getModes();
	return tmp;
	//#pwat :+t
}

std::string CodeBuilder::toStringRPL_ENDOFWHO(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;

	std::string tmp = " :End of WHO list";
	if (channel)
		tmp = channel->getName() + tmp;
	return tmp;
	//"<name> :End of WHO list"
}

std::string CodeBuilder::toStringRPL_WHOREPLY(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;

	std::string acc = "";
	std::string sep = "";

	if (!channel)
		return acc;
	t_client_modes &clients = channel->getClients();
	for (t_client_modes::const_iterator it = clients.begin(); it != clients.end(); it++)
	{
		acc += sep + channel->getName() + " :" + client->getUserOnHost() + " " + server->getFullClientID(client) + " " + server->getHost() + " " + it->second.first->getNick() + " " + channel->clientModesToString(it->second.first) + " :" + it->second.first->getRealName();
		sep = "\n";
	}
	return acc;
	// #pwat user42 user.ft-irc.42.fr ft-irc.42.fr user42__ H@ :0 realname
}

std::string CodeBuilder::toStringERR_UMODEUNKNOWNFLAG(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;
	return ":Unknown MODE flag";
}

std::string CodeBuilder::toStringERR_USERSDONTMATCH(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;
	return ":Cannot change mode for other users";
}

// somehow, should not be used even if mentionned in doc
std::string CodeBuilder::toStringRPL_UMODEIS(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;
	return server->getFullClientID(client) + " MODE " + client->getNick() + " :" + *s + client->modeToString();
}

std::string CodeBuilder::toStringPLACEHOLDER(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;

	return ":I AM A PLACEHOLDER ";
}

std::string CodeBuilder::toStringERR_NOORIGIN(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	(void)s;

	return ":No origin specified";
}
std::string CodeBuilder::toStringRPL_TIME(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	(void)s;

	time_t now(time(NULL));
	std::string time(ctime(&now));
	time.erase(time.size() - 1, 1);

	return server->getHost() + " :" + time;
}
std::string CodeBuilder::toStringRPL_ADMINME(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	(void)s;

	return server->getHost() + " :Administrative info";
}
std::string CodeBuilder::toStringRPL_ADMINLOC1(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	(void)s;

	return "Name: mida,thi-nguy,so";
}
std::string CodeBuilder::toStringRPL_ADMINLOC2(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	(void)s;

	return "Location: Paris FR";
}
std::string CodeBuilder::toStringRPL_ADMINEMAIL(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	(void)s;

	return "Email: ourirc.42.paris.fr";
}
std::string CodeBuilder::toStringRPL_MOTDSTART(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	(void)s;

	return "ourirc Message of the day -";
}
std::string CodeBuilder::toStringRPL_MOTD(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	(void)s;
	std::string tmp = "  /\\_/\\  (";
	std::string tmp2 = " ( ^.^ ) _)";
	std::string tmp3 = "  \\   / (";
	std::string tmp4 = " ( | | )";
	std::string tmp5 = "(__d b__)";

	return tmp + "\n" + tmp2 + "\n" + tmp3 + "\n" + tmp4 + "\n" + tmp5;
}
std::string CodeBuilder::toStringRPL_ENDOFMOTD(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	(void)s;

	return " ---------------- End of MOTD -------------------";
}
std::string CodeBuilder::toStringERR_NOMOTD(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	(void)s;

	return ":MOTD File is missing";
}
std::string CodeBuilder::toStringERR_NOSUCHCHANNEL(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	(void)s;

	return " :No such channel";
}
std::string CodeBuilder::toStringERR_NOTONCHANNEL(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	(void)s;

	return " :You're not on that channel";
}
std::string CodeBuilder::toStringERR_NOSUCHSERVER(std::string *server_name, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;

	return *server_name + " :No such server";
}
std::string CodeBuilder::toStringRPL_UNAWAY(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	(void)s;

	return ":You are no longer marked as being away";
}

std::string CodeBuilder::toStringRPL_ENDOFNAMES(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;

	std::string str = " :End of NAMES list.";
	std::string tmp = "";
	if (channel)
		tmp = channel->getName() + str;
	else if (!channel && s) // bit weird but ok
		tmp = (*s) + str;
	return tmp;
	//"<channel> :End of NAMES list"
}

std::string CodeBuilder::toStringRPL_NOWAWAY(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	(void)s;

	return ":You have been marked as being away";
}
std::string CodeBuilder::toStringRPL_AWAY(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	(void)s;

	return client->getNick() + " :" + client->get_awayMsg();
}
std::string CodeBuilder::toStringERR_USERNOTINCHANNEL(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;
	std::string tmp = client->getNick() + " ";
	if (channel)
		tmp += channel->getName();
	tmp += ":They aren't on that channel";
	return tmp; //"<nick> <channel> :They aren't on that channel"
}

std::string CodeBuilder::toStringRPL_INVITING(std::string *clientDestNick, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	std::string tmp = "";
	tmp += *clientDestNick;

	if (channel)
		tmp += " " + channel->getName();
	return tmp;
}
//"<channel> <nick>"//Somehow wrong, I had to swap the order

std::string CodeBuilder::toStringERR_USERONCHANNEL(std::string *target, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)channel;
	std::string tmp = *target;
	if (channel)
		tmp += " " + channel->getName();
	tmp += " :is already on channel";

	return tmp;
} //"<user> <channel> :is already on channel"

std::string CodeBuilder::toStringERR_CHANOPRIVSNEEDED(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;

	std::string tmp = "";
	if (channel)
		tmp += channel->getName();
	tmp += " :You're not channel operator";
	return tmp; //"<channel> :You're not channel operator"
}

std::string CodeBuilder::toStringRPL_NOTOPIC(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;

	std::string tmp = "";
	if (channel)
		tmp += channel->getName();
	tmp += " :No topic is set";
	return tmp; //"<channel> :No topic is set"
}
std::string CodeBuilder::toStringERR_NOPRIVILEGES(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;
	return ":Permission Denied- You're not an IRC operator";
}

std::string CodeBuilder::toStringRPL_LISTSTART(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;

	return " Channel :Users Name";
	//" Channel :Users Name"
}

std::string CodeBuilder::toStringRPL_LIST(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;

	std::stringstream ss;
	
	ss << " " << channel->getName() << " " << channel->getClients().size() << " :" << channel->getTopic() << END_OF_COMMAND;

	return ss.str();
}

std::string CodeBuilder::toStringRPL_LISTEND(std::string *s, MasterServer *server, Client *client, Channel *channel)
{
	(void)server;
	(void)client;
	(void)s;
	(void)channel;

	return " :End /LIST";
	//" :End of /LIST"
}
/* ************************************************************************** */