#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <map>
#include <string>
#include "Client.hpp"
#include "MasterServer.hpp"
#include "../../includes/enumFactory.h"

#define E_MODE_CHANNEL_ENUM(XX)                        \
	XX(_MOD_CHANNEL_NO_FLAGS, = (1u << 0))             \
	XX(_MOD_CHANNEL_FLAG_CREATOR, = (1u << 1))         \
	XX(_MOD_CHANNEL_FLAG_OPERATOR, = (1u << 2))        \
	XX(_MOD_CHANNEL_FLAG_VOICE, = (1u << 3))           \
	XX(_MOD_CHANNEL_FLAG_ANONYMOUS, = (1u << 4))       \
	XX(_MOD_CHANNEL_FLAG_INVITE_ONLY, = (1u << 5))     \
	XX(_MOD_CHANNEL_FLAG_MODERATED, = (1u << 6))       \
	XX(_MOD_CHANNEL_FLAG_NO_MESSAGE, = (1u << 7))      \
	XX(_MOD_CHANNEL_FLAG_QUIET, = (1u << 8))           \
	XX(_MOD_CHANNEL_FLAG_PRIVATE, = (1u << 9))         \
	XX(_MOD_CHANNEL_FLAG_SECRET, = (1u << 10))         \
	XX(_MOD_CHANNEL_FLAG_REOP, = (1u << 11))           \
	XX(_MOD_CHANNEL_FLAG_TOPIC_SETTABLE, = (1u << 12)) \
	XX(_MOD_CHANNEL_FLAG_KEY, = (1u << 13))            \
	XX(_MOD_CHANNEL_FLAG_USER_LIMIT, = (1u << 14))     \
	XX(_MOD_CHANNEL_FLAG_KEEP_OUT, = (1u << 15))       \
	XX(_MOD_CHANNEL_FLAG_BAN_MASK, = (1u << 16))       \
	XX(_MOD_CHANNEL_FLAG_INVITATION_MASK, = (1u << 17))

//_MOD_CHANNEL_FLAG_CREATOR 		 O - give "channel creator" status;
//_MOD_CHANNEL_FLAG_OPERATOR 		 o - give/take channel operator privilege;
//_MOD_CHANNEL_FLAG_VOICE	 		 v - give/take the voice privilege;
//_MOD_CHANNEL_FLAG_ANONYMOUS 		 a - toggle the anonymous channel flag;
//_MOD_CHANNEL_FLAG_INVITE_ONLY		 i - toggle the invite-only channel flag;
//_MOD_CHANNEL_FLAG_MODERATED 		 m - toggle the moderated channel;
//_MOD_CHANNEL_FLAG_NO_MESSAGE 		 n - toggle the no messages to channel from clients on the
//					 		  		   	 outside;
//_MOD_CHANNEL_FLAG_QUIET	 		 q - toggle the quiet channel flag;
//_MOD_CHANNEL_FLAG_PRIVATE 		 p - toggle the private channel flag;
//_MOD_CHANNEL_FLAG_SECRET 			 s - toggle the secret channel flag;
//_MOD_CHANNEL_FLAG_REOP	 		 r - toggle the server reop channel flag;
//_MOD_CHANNEL_FLAG_TOPIC_SETTABLE	 t - toggle the topic settable by channel operator only flag;
//_MOD_CHANNEL_FLAG_KEY 			 k - set/remove the channel key (password);
//_MOD_CHANNEL_FLAG_USER_LIMIT 		 l - set/remove the user limit to channel;
//_MOD_CHANNEL_FLAG_KEEP_OUT 		 b - set/remove ban mask to keep users out;
//_MOD_CHANNEL_FLAG_BAN_MASK 		 e - set/remove an exception mask to override a ban mask;
//_MOD_CHANNEL_FLAG_INVITATION_MASK  I - set/remove an invitation mask to automatically override
//   									 the invite-only flag;

DECLARE_ENUM(e_mode_channel, E_MODE_CHANNEL_ENUM)
//				id				value			applyMode			if add is false, then it's getting rid of
typedef std::map<char, std::pair<e_mode_channel, bool (Channel::*)(bool, MasterServer *, std::string, t_client_ParsedCmd &)> > t_char_channel_mode_dictionary;

// fd							client		flags
typedef std::map<int, std::pair<Client *, int> > t_client_modes;

class Channel
{
public:
	Channel(std::string name = "");
	~Channel();
	std::string clientListToString(bool with_invisible);
	std::string getName();
	std::string getTopic();
	std::string getModes();
	t_client_modes &getClients();
	std::string clientModesToString(Client *c);
	bool isOperatorHere(Client *c);

	Client *findClientWithNick(std::string nick);
	bool addMode(int fd, e_mode_channel mode);
	bool minusMode(int fd, e_mode_channel mode);
	void sendToWholeChannel(MasterServer *serv, std::string message, Client *exclude = NULL);
	void join(MasterServer *serv, Client *client);
	bool quit(Client *client);
	bool quit_part(MasterServer *serv, Client *client, std::string base);
	bool kick(std::string name_victim, MasterServer *serv, Client *client, std::string notification);

	static e_mode_channel stringToMode(std::string s);
	static std::string modeToString(e_mode_channel modes);
	std::string modeToString() const;
	static t_char_channel_mode_dictionary charChannelModeDictionnary;
	static t_char_channel_mode_dictionary initCharChannelModeDictionnary();

	bool applyMode(std::string target_modes, MasterServer *serv, std::string base, t_client_ParsedCmd &parsed_command);
	bool applyOperatorMode(bool add, MasterServer *serv, std::string base, t_client_ParsedCmd &parsed_command);
	class unknownModeException : public std::exception
	{
	public:
		unknownModeException(void) {}
		virtual const char *what() const throw()
		{
			return "unknownModeException";
		}
	};

private:
	Channel(Channel const &src);
	Channel &operator=(Channel const &rhs);

	const std::string _name;
	const std::string _topic;
	t_client_modes _clients;
	e_mode_channel _modes;
};

std::ostream &operator<<(std::ostream &o, Channel const &i);

#endif /* ********************************************************* CHANNEL_H */