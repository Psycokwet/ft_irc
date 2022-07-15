#include "../network/MasterServer.hpp"
/*
** ---------------------------------- AWAY ----------------------------------
**
**     Command: AWAY
   Parameters: [ <text> ]

   With the AWAY command, clients can set an automatic reply string for
   any PRIVMSG commands directed at them (not to a channel they are on).
   The server sends an automatic reply to the client sending the PRIVMSG
   command.  The only replying server is the one to which the sending
   client is connected to.

   The AWAY command is used either with one parameter, to set an AWAY
   message, or with no parameters, to remove the AWAY message.

   Because of its high cost (memory and bandwidth wise), the AWAY
   message SHOULD only be used for client-server communication.  A
   server MAY choose to silently ignore AWAY messages received from
   other servers.  To update the away status of a client across servers,
   the user mode 'a' SHOULD be used instead.  (See Section 3.1.5)

   Numeric Replies:

           RPL_UNAWAY                    RPL_NOWAWAY


*/

bool MasterServer::execAWAY(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
    (void)base;
    (void)parsed_command;
    (void)respQueue;
    Client *client = parsed_command.first; // should not be null regarding how we got here

    lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
    if (params.size())
    {
        client->addMode(_MOD_FLAG_AWAY);
        pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_UNAWAY, this, client, &base), respQueue);
        return true;
    }
    else
        pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_NOWAWAY, this, client, &base), respQueue);

    return true;
}
