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

bool MasterServer::execQUIT(std::string base, t_client_ParsedCmd &parsed_command)
{
	(void)base;
	(void)parsed_command;
	Client *client = parsed_command.first;
	std::string notification = ":" + getFullClientID(client) + " " + base;
	sendToWholeServer(notification, client);
	return false;
}