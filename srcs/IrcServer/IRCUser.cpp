#include "IRCServer.hpp"

// sup les user dans le channel
void IRCServer::remove(User *user)
{
    std::map<std::string, Channel *> chanCopy(_channels);
    Channel *chan;
    for (std::map<std::string, Channel *>::iterator it(chanCopy.begin());
         it != chanCopy.end(); ++it)
    {
        chan = it->second;
        if (chan->isUser(user))
            leave(user, chan);
        else if (chan->isInvited(user))
            chan->_userInv.erase(user);
    }
}

void IRCServer::leave(User *user, Channel *chan)
{
    user->_add.erase(chan);
    if (chan->RemoveUser(user) == 0)
    {
        _channels.erase(chan->_name);
        delete chan;
    }
}

void IRCServer::welcome(User *user, std::vector<t_clientCmd> &respQueue)
{
}
