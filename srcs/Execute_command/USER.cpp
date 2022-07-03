#include "../IrcServer/IRCServer.hpp"
/*
** ---------------------------------- USER ----------------------------------
  check la taille param

*/

bool IRCServer::execUSER(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
    std::string response;

    if ((((*(parsed_command.second))[MESSAGE]).size()) < 4)
    {
        response = ":Not enough parameters"; // ERR_NEEDMOREPARAMS 461
        pushToQueue(parsed_command.first, response, respQueue);
    }
    if (((*(parsed_command.second))[PARAMS]).empty())
    {
        response = ":Not enough parameters"; // ERR_NEEDMOREPARAMS 461
        pushToQueue(parsed_command.first, response, respQueue);
    }
    if (!response.empty())
        pushToQueue(parsed_command.first, response, respQueue);

    return true;
}
