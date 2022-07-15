#include "../network/MasterServer.hpp"

/*
** ---------------------------------- KICK ----------------------------------
  Command: KICK
   Parameters: <channel> *( "," <channel> ) <user> *( "," <user> )
               [<comment>]

   The KICK command can be used to request the forced removal of a user
   from a channel.  It causes the <user> to PART from the <channel> by
   force.  For the message to be syntactically correct, there MUST be
   either one channel parameter and multiple user parameter, or as many
   channel parameters as there are user parameters.  If a "comment" is
   given, this will be sent instead of the default message, the nickname
   of the user issuing the KICK.

   The server MUST NOT send KICK messages with multiple channels or
   users to clients.  This is necessarily to maintain backward
   compatibility with old client software.

   Numeric Replies:

           -ERR_NEEDMOREPARAMS              -ERR_NOSUCHCHANNEL
           ERR_BADCHANMASK                 -ERR_CHANOPRIVSNEEDED=op
           ERR_USERNOTINCHANNEL            -ERR_NOTONCHANNEL
*/

bool MasterServer::execKICK(std::string base, t_client_ParsedCmd &parsed_command)
{
    (void)base;
    (void)parsed_command;
    Client *client = parsed_command.first;

    lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
    lazyParsedSubType channels(((*(parsed_command.second))[CHANNELS]));
    if (params.size())
    {
        pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NEEDMOREPARAMS, this, client, &base));
        return true;
    }
    for (lazyParsedSubType::iterator it = channels.begin(); it != channels.end(); it++)
    {
        Channel *chan = findChanneWithName(*it);
        if (!chan)
        {
            pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOSUCHCHANNEL, this, client));
            continue;
        }
        if (chan->quit_part(this, client, base) == false)
        {
            pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOTONCHANNEL, this, client));
            continue;
        }
        if (!chan->isOperatorHere(client))
        {
            pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_CHANOPRIVSNEEDED, this, client));
            continue;
        }
    }
    return true;
}
