#include "../network/MasterServer.hpp"

/*
** ---------------------------------- OPER ----------------------------------
**
**    Command: OPER
   Parameters: <name> <password>

   A normal user uses the OPER command to obtain operator privileges.
   The combination of <name> and <password> are REQUIRED to gain
   Operator privileges.  Upon success, the user will receive a MODE
   message (see section 3.1.5) indicating the new user modes.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              RPL_YOUREOPER
           ERR_NOOPERHOST                  ERR_PASSWDMISMATCH

   Example:

   OPER foo bar                    ; Attempt to register as an operator
                                   using a username of "foo" and "bar"
                                   as the password.
*/

bool MasterServer::execOPER(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
    (void)base;
    (void)parsed_command;
    (void)respQueue;
    Client *client = parsed_command.first;
    std::string oper_nick = "admin";
    std::string oper_pass = "ourirc";

    lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
    lazyParsedSubType message(((*(parsed_command.second))[MESSAGE]));

    if (params.size() < 2)
    {
        pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NEEDMOREPARAMS, this, client, &base), respQueue);
        return true;
    }
    if (params.front() != oper_nick || message.front() != oper_pass)
    {
        pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_PASSWDMISMATCH, this, client, &base), respQueue);
        return true;
    }
    else
    {
        client->_oper = true;
        pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_YOUREOPER, this, client, &base), respQueue);
        return true;
    }
    return true;
}