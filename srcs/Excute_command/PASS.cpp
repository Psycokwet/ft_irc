#include "../IrcServer/IRCServer.hpp"

void IrcServer::PASS(t_client_ParsedCmd command, std::vector<t_clientCmd> &respQueue)
{
    User *user();

    std::string resp;

    if (user->_passOK)
        // resp =  ERR_ALREADYREGISTRED
        if (cmd._params.empty())
            // resp = (user, ERR_NEEDMOREPARAMS

            else if (cmd._params[0] == _svPassword) // server password
                user->_passwordOK = true;
    if (!resp.empty())
        pushToQueue(user->_fd, resp, responseQueue);
}