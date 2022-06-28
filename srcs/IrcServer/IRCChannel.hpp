#include "IRCServer.hpp"

// creation dun new channel
Channel *IRCServer::newChannel(std::string const &name, User *creat)
{
    Channel *chan(new Channel(name, creat));
    _channel_list[name] = chan;
    creat->_add.insert(chan);
    return chan;
}

// user ajout autre user sur un meme channel
std::set<User *> IRCServer::getCommonUser(User *user) const
{
    std::set<User *> results;
    std::set<Channel *>::iterator it;
    for (it = user->_add.begin(); it != user->_add.end(); ++it)
        results.insert((*it)->_user.begin(), (*it)->_user.end());
    results.erase(user);
    return results;
}

// return pointer du channel trouve sinon null
Channel *IRCServer::getChannelName(std::string const &name) const
{
    if (_channel_list.find(name) != _channel_list.end())
        return _channel_list.at(name);
    return NULL;
}