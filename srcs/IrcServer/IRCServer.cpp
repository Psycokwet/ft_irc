#include "IRCServer.hpp"

/*
** ---------------------------------- STATIC ----------------------------------
*/


/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
IRCServer::IRCServer(std::string const &password):
    _password(password)
{}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/
IRCServer::~IRCServer()
{
    std::map<int, User *>::iterator itUser;
    std::map<int, Channel *>::iterator itChannel;

    for (itUser = _users.begin(); itUser != _users.end(); ++itUser)
        delete itUser->second;
    for (itChannel = _channels.begin(); itChannel != _channels.end(); ++itChannel)
        delete itChannel->second;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- PUBLIC METHODS ---------------------------
*/
void    IRCServer::removeDisconnectUser(int fd)
{
    if(_users.find(fd) != _users.end())
    {
        User *one_user = _users[fd];
        if (one_user->getRegistered() == true)
            removeUserFromAllChannels(one_user);
        delete one_user;
        _users.erase(fd);
    }
}

// Called by the server. Process a command from a client, then queue responses
// into responseQueue. Return true if client is disconnecting, otherwise false.
bool    IRCServer::processCommand(t_clientCmd const &command, std::vector<t_clientCmd> &respQueue)
{
    User    *one_user;
    int     fd = command.first;

    // ! Need to finish this (execCommand here)



}

// Get the fd being killed by a server operator
int     IRCServer::getVictim()
{
    int ret = _fdToKill;
    _fdToKill = -1;
    return ret;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/



/*
** --------------------------------- PRIVATE METHODS --------------------------
*/
void	IRCServer::removeUserFromAllChannels(User *user)
{
    // ! update user in channel


}