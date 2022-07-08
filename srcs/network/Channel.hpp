#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <map>
#include <string>
#include "Client.hpp"
#include "MasterServer.hpp"
#include "ClientMode.hpp"

typedef std::map<int, std::pair<Client *, ClientMode *> > t_client_modes;

class Channel
{
public:
	Channel(std::string name);
	~Channel();
	void sendToWholeChannel(std::vector<t_clientCmd> &respQueue, MasterServer *serv, std::string message, Client *exclude = NULL);
	void join(std::vector<t_clientCmd> &respQueue, MasterServer *serv, Client *client);
	void quit(std::vector<t_clientCmd> &respQueue, MasterServer *serv, Client *client);

private:
	Channel(Channel const &src);
	Channel &operator=(Channel const &rhs);

	const std::string _name;
	t_client_modes _clients;
};

std::ostream &operator<<(std::ostream &o, Channel const &i);

#endif /* ********************************************************* CHANNEL_H */