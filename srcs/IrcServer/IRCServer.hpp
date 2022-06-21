#ifndef IRCServer_HPP
#define IRCServer_HPP

#include "../Channel/Channel.hpp"
#include "../User/User.hpp"
#include "../../includes/ft_irc.hpp"
#include "../../includes/code.hpp"



class IRCServer
{
    private :

    std::map<int, User *>		           _User;		// Users list
	std::map<std::string, Channel *>	_channels;	// Channels list

    int	_killing; //fd users killing by operator


    // USERS //

    void	leave(User *user, Channel *chan); //leave channel
	void	remove(User *user);//remove all channel
    void    welcome();




    // CHANNEL //

    Channel	*newChannel(std::string const &name, User *creator);
	std::set<User *>	getCommonUser(User *user) const;

    public:

	IRCServer(std::string const &password);
	virtual ~IRCServer();

	User	*getUserByNick(std::string const &nick) const;
	Channel	*getChannelByName(std::string const &name) const;

};

#endif