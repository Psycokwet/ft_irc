#ifndef USER_HPP
#define USER_HPP

#include "../../includes/ft_irc.hpp"
#include "../Channel/Channel.hpp"

class User
{
    public: 


    private:
        int                  _fd;            // is the fd of client socket
        std::set<Channel *>  _joinedList;    // List of channels user has joined
};

#endif