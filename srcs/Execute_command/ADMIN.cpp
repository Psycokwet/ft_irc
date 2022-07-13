#include "../network/MasterServer.hpp"

/*
** ---------------------------------- ADMIN ----------------------------------
 Command: ADMIN
   Parameters: [ <target> ]

   The admin command is used to find information about the administrator
   of the given server, or current server if <target> parameter is
   omitted.  Each server MUST have the ability to forward ADMIN messages
   to other servers.

   Wildcards are allowed in the <target> parameter.

   Numeric Replies:

           ERR_NOSUCHSERVER
           RPL_ADMINME                   RPL_ADMINLOC1
           RPL_ADMINLOC2                 RPL_ADMINEMAIL

   Examples:

   ADMIN tolsun.oulu.fi            ; request an ADMIN reply from
                                   tolsun.oulu.fi

   ADMIN syrk                      ; ADMIN request for the server to
                                   which the user syrk is connected


*/

bool MasterServer::execADMIN(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
  (void)base;
  (void)parsed_command;
  (void)respQueue;
  Client *client = parsed_command.first;

  pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_ADMINME, this, client, &base), respQueue);
  pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_ADMINLOC1, this, client, &base), respQueue);
  pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_ADMINLOC2, this, client, &base), respQueue);
  pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_ADMINEMAIL, this, client, &base), respQueue);

  return (true);
}
