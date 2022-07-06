#include "../IrcServer/IRCServer.hpp"

/*
** ---------------------------------- PASS ----------------------------------
  Ckeck password users

*/

bool IRCServer::execPASS(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
    std::string response;

    if (((*(parsed_command.second))[PARAMS]).empty())
    {
        response = ":Not enough parameters"; // ERR_NEEDMOREPARAMS 461
        pushToQueue(parsed_command.first, response, respQueue);
    }
    /*if (((*(parsed_command.second))[PARAMS]).front())
    {
        response = " :You may not reregister"; // ERR_ALREADYREGISTERED 462
        pushToQueue(parsed_command.first, response, respQueue);
        return true;
    }
    else if ( != _serverPassword)
    {
        response = " :Password incorrect"; // ERR_PASSWDMISMATCH 464
        pushToQueue(parsed_command.first, response, respQueue);
    }
    if (!response.empty())
        pushToQueue(parsed_command.first, response, respQueue);*/
    return true;
}
