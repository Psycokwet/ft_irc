#ifndef IRCServer_HPP
#define IRCServer_HPP

#include "../../includes/ft_irc.hpp"
#include "../Channel/Channel.hpp"
#include "../User/User.hpp"

class IRCServer
{
    public: 


    private:
        std::map< int, User * >		            _users;		// Users list
        std::map< std::string, Channel * >	    _channels;	// Channels list

};

#endif