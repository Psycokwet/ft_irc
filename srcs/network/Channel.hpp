#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <map>
#include <string>
#include "Client.hpp"
#include "MasterServer.hpp"
#include "../../includes/enumFactory.h"

#define _MOD_NO_FLAGS 0
#define _MOD_FLAG_ADMIN 1
typedef std::map<int, std::pair<Client *, int> > t_client_modes;

class Channel
{
public:
	Channel(std::string name);
	~Channel();
	std::string clientListToString();
	std::string getName();
	std::string getTopic();
	void sendToWholeChannel(std::vector<t_clientCmd> &respQueue, MasterServer *serv, std::string message, Client *exclude = NULL);
	void join(std::vector<t_clientCmd> &respQueue, MasterServer *serv, Client *client, std::string base = "");
	void quit(std::vector<t_clientCmd> &respQueue, MasterServer *serv, Client *client);

private:
	Channel(Channel const &src);
	Channel &operator=(Channel const &rhs);

	const std::string _name;
	const std::string _topic;
	t_client_modes _clients;
};

std::ostream &operator<<(std::ostream &o, Channel const &i);

#endif /* ********************************************************* CHANNEL_H */