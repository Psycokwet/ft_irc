#include "../network/MasterServer.hpp"

/*
** ---------------------------------- LIST ----------------------------------
**  Command: LIST
**     Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
**  
**     The list command is used to list channels and their topics.  If the
**     <channel> parameter is used, only the status of that channel is
**     displayed.
**  
**     If the <target> parameter is specified, the request is forwarded to
**     that server which will generate the reply.
**  
**     Wildcards are allowed in the <target> parameter.
**  
**     Numeric Replies:
**  
**             ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
**             RPL_LIST                        RPL_LISTEND
**  
**     Examples:
**  
**     LIST                            ; Command to list all channels.
**  
**     LIST #twilight_zone,#42         ; Command to list channels
**                                     #twilight_zone and #42
*/

bool MasterServer::execLIST(std::string base, t_client_ParsedCmd &parsed_command)
{
    (void)base;
	(void)parsed_command;

    Client *client = parsed_command.first; // should not be null regarding how we got here
    
    pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_LISTSTART, this, client, &base));
    for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
    {
        pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_LIST, this, client, &base, it->second));
    }
    pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_LISTEND, this, client, &base));
    return true;
}