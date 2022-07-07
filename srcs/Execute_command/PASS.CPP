#include "../IrcServer/IRCServer.hpp"

/*
** ---------------------------------- PASS ----------------------------------
    Command: PASS
   Parameters: <password>

   The PASS command is used to set a 'connection password'.  The
   optional password can and MUST be set before any attempt to register
   the connection is made.  Currently this requires that user send a
   PASS command before sending the NICK/USER combination.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

   Example:

           PASS secretpasswordhere

*/
bool IRCServer::execPASS(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
    std::string response;

    if (((*(parsed_command.second))[PARAMS]).empty())
    {
        response = " :Not enough parameters"; // ERR_NEEDMOREPARAMS 461
        pushToQueue(parsed_command.first, response, respQueue);
    }
    if (((*(parsed_command.second))[PARAMS].front()) != _serverPassword && (IRCServer::getRegistered() == false))
    {
        response = " :You may not reregister"; // ERR_ALREADYREGISTERED 462
        pushToQueue(parsed_command.first, response, respQueue);
    }
    if (((*(parsed_command.second))[PARAMS].front()) == _serverPassword)
        IRCServer::one_user->_passOK = true;
    if (!response.empty())
        pushToQueue(parsed_command.first, response, respQueue);
    return true;
}
