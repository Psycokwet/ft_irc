#include "../network/MasterServer.hpp"

/*
** ---------------------------------- VERSION ----------------------------------
**  Command: VERSION
   Parameters: [ <target> ]

   The VERSION command is used to query the version of the server
   program.  An optional parameter <target> is used to query the version
   of the server program which a client is not directly connected to.

   Wildcards are allowed in the <target> parameter.

   Numeric Replies:

           ERR_NOSUCHSERVER                RPL_VERSION

   Examples:

   VERSION tolsun.oulu.fi          ; Command to check the version of
                                   server "tolsun.oulu.fi".

**/
bool MasterServer::execVERSION(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
        (void)base;
        (void)parsed_command;
        (void)respQueue;
        Client *client = parsed_command.first; // should not be null regarding how we got here

        client->getNick();
        pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_VERSION, this, client, &base), respQueue);
        return true;
}