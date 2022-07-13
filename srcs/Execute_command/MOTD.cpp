#include "../network/MasterServer.hpp"

/*
** ---------------------------------- MOTD ----------------------------------
Command: MOTD
   Parameters: [ <target> ]

   The MOTD command is used to get the "Message Of The Day" of the given
   server, or current server if <target> is omitted.

   Wildcards are allowed in the <target> parameter.

   Numeric Replies:
           RPL_MOTDSTART                   RPL_MOTD
           RPL_ENDOFMOTD                   ERR_NOMOTD

*/

bool MasterServer::execMOTD(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
    (void)base;
    (void)parsed_command;
    (void)respQueue;
    Client *client = parsed_command.first;

    pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_MOTDSTART, this, client, &base), respQueue);
    pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_MOTD, this, client, &base), respQueue);
    pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_ENDOFMOTD, this, client, &base), respQueue);
    return (true);
}
