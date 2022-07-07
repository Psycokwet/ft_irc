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
    Client *client = parsed_command.first; // should not be null regarding hgow we got here
    if (client->_passOK)
    {
        pushToQueue(client->_fd, ": You may not reregister", respQueue);
        // already registered
        std::cout << "1\n";
        return false;
    }

    lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));

    switch (params.size())
    {
    case 0:
        pushToQueue(client->_fd, ": Not enough parameters", respQueue); // ERR_NEEDMOREPARAMS 461
        break;
    case 1:
        if (params.front() == _serverPassword)
        {
            client->_passOK = true;
            return true;
        }
        else
            pushToQueue(client->_fd, ": Password incorrect", respQueue); // ERR_PASSWDMISMATCH 464
        break;

    default:
        pushToQueue(client->_fd, TOO_MANY_ARGS, respQueue);
        // too much params
        break;
    }
    return false;
}
