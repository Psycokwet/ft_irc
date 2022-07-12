#include "../network/MasterServer.hpp"
/*
** ---------------------------------- QUIT ----------------------------------
Command: QUIT
   Parameters: [ <Quit Message> ]

   A client session is terminated with a quit message.  The server
   acknowledges this by sending an ERROR message to the client.

   Numeric Replies:

           None.

   Example:

   QUIT :Gone to have lunch        ; Preferred message format.

 :idamouttou!idamouttou@localhost QUIT :Quit: Leaving\r\n
:syrk!kalt@millennium.stealth.net QUIT :Gone to have lunch ; User
                                   syrk has quit IRC to have lunch.
*/

bool MasterServer::execQUIT(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
        (void)base;
        (void)parsed_command;
        (void)respQueue;
        Client *client = parsed_command.first;
        std::set;

        lazyParsedSubType message(((*(parsed_command.second))[MESSAGE]));

        if (message.size())
        {
                pushToQueue(client->_fd, ":" + client->getUserOnHost() + "!" + client->getUserOnHost() + "@" + MasterServer::getServerName() + ".net " + base, respQueue);
                return false;
        }
        {
        }
}

/*
User *user(cmd._user);
        string msg = cmd._params.empty()? "Client exited": ("Quit: " + cmd._params[0]);
        // Inform everyone user is leaving
        appendUserNotif(user,(string[]){"QUIT", ":" + msg, ""},getCommonUsers(user), responseQueue);
        string resp(getErrorResponse(user, msg));
        pushToQueue(user->_fd, resp, responseQueue);
        ClientDisconnect(user->_fd);*/