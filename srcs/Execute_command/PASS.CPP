#include "../IrcServer/IRCServer.hpp"

bool IRCServer::execPASS(t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
     User *user;
     std::string response;

    if ( ((*(parsed_command.second))[PARAMS]).empty() )
	    {
		    response = ":Not enough parameters";
		    //pushToQueue(parsed_command.first, response, respQueue);
	    }
    if ((user._passOK))
        {
            response = ":You may not reregister";
            //pushToQueue(parsed_command.first, response, respQueue);
        }
    return true;
}