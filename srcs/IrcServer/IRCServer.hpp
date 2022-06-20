#ifndef IRCServer_HPP
#define IRCServer_HPP

#include "../../includes/ft_irc.hpp"
#include "../Channel/Channel.hpp"
#include "../User/User.hpp"

class User;
class Channel;

class IRCServer
{
    public:
        IRCServer(std::string const &password);
        ~IRCServer();

        void    removeDisconnectUser(int fd);
        bool    processCommand(t_clientCmd const &command, std::vector<t_clientCmd> &respQueue);
        int     getVictim();



    private:
        std::map< int, User * >		            _users;		// Users list
        std::map< std::string, Channel * >	    _channels;	// Channels list
        std::string const                       _password;
        int                                     _fdToKill;  // Fd of user killed by operater

        void	removeUserFromAllChannels(User *user);
};

#endif