#include "../network/MasterServer.hpp"
/*
** ---------------------------------- MODE USER OR CHANNEL ----------------------------------
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
        std::string msg;
        Client *client = parsed_command.first;

        lazyParsedSubType message(((*(parsed_command.second))[MESSAGE]));

        if (message.size())
        {
                pushToQueue(client->_fd, ":" + client->getUserOnHost() + "!" + client->getUserOnHost() + "@" + MasterServer::getServerName() + ".net " + base, respQueue);
                return false;
        }
        return false;
}