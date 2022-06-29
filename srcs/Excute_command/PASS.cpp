#include "../IrcServer/IRCServer.hpp"

void IrcServer::PASS(Command const &cmd, std::vector<t_clientCmd> &respQueue)
{
    User *user();

    std::string resp;

    if (user->_passOK)
        // resp = get ERR_ALREADYREGISTRED
        if (cmd._params.empty())
            resp = getResponseFromCode(user, ERR_NEEDMOREPARAMS, (string[]){cmd._type});
        else if (cmd._params[0] == _svPassword)
            user->_passwordOK = true;
    if (!resp.empty())
        pushToQueue(user->_fd, resp, responseQueue);
}