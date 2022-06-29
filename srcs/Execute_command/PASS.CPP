#include "IRCServer.hpp"

void IRCServer::PASS(t_client_ParsedCmd command, std::vector<t_clientCmd> &respQueue)
{
    User *user;
    std::string response;

    // check password
    if (user->_passOK)
        response = ERR_ALREADYREGISTRED;
    // check parametre
    if (_params.empty())
        response = ERR_NEEDMOREPARAMS;
    // else if (_params ==  _serverPassword)
    //   user->_passOK = true;
}