#include "../network/MasterServer.hpp"
/*
** ---------------------------------- USER ----------------------------------
  Command: USER
   Parameters: <user> <mode> <unused> <realname>

   The USER command is used at the beginning of connection to specify
   the username, hostname and realname of a new user.

   The <mode> parameter should be a numeric, and can be used to
   automatically set user modes when registering with the server.  This
   parameter is a bitmask, with only 2 bits having any signification: if
   the bit 2 is set, the user mode 'w' will be set and if the bit 3 is
   set, the user mode 'i' will be set.  (See Section 3.1.5 "User
   Modes").

   The <realname> may contain space characters.

   Numeric Replies:

		   ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

   Example:

   USER guest 0 * :Ronnie Reagan   ; User registering themselves with a
								   username of "guest" and real name
								   "Ronnie Reagan".

   USER guest 8 * :Ronnie Reagan   ; User registering themselves with a
								   username of "guest" and real name
								   "Ronnie Reagan", and asking to be set
								   invisible.



*/

bool MasterServer::execUSER(std::string base, t_client_ParsedCmd &parsed_command)
{

	(void)base;
	(void)parsed_command;
	Client *client = parsed_command.first; // should not be null regarding how we got here

	if (client->_userOnHost != "")
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_ALREADYREGISTRED, this, client, &base));
		return true;
	}
	lazyParsedSubType params(((*(parsed_command.second))[PARAMS]));
	lazyParsedSubType message(((*(parsed_command.second))[MESSAGE]));
	if (!params.size() || !message.size())
	{
		pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NEEDMOREPARAMS, this, client, &base));
		return true;
	}
	std::string realName = message.front();
	std::string userName = params.front();
	client->_userOnHost = userName;
	client->_realName = realName;
	// mode stuff to do see later
	client->validatedRegistration(this);

	return true;
}
