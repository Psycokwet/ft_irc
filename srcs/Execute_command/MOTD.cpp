#include "../network/MasterServer.hpp"

/*
** ---------------------------------- MOTD ----------------------------------
Command: MOTD
   Parameters: [ <target> ]

   The MOTD command is used to get the "Message Of The Day" of the given
   server, or current server if <target> is omitted.

   Wildcards are allowed in the <target> parameter.

   Numeric Replies:
           RPL_MOTDSTART                   RPL_MOTD
           RPL_ENDOFMOTD                   ERR_NOMOTD

*/
static bool motdInit(false);
static std::vector<std::string> MOTDLines;

static void initMOTD()
{
    motdInit = true;
    std::ifstream motdFile(MOTD_FILE);
    if (!motdFile.is_open())
    {
        char *cwd(getcwd(NULL, 0));
        std::cout << "Cannot read message of the day from "
                  << cwd << '/' << MOTD_FILE << '\n';
        free(cwd);
        return;
    }

    std::string line;
    while (std::getline(motdFile, line))
        MOTDLines.push_back(line);
    motdFile.close();
}

bool MasterServer::execMOTD(std::string base, t_client_ParsedCmd &parsed_command, std::vector<t_clientCmd> &respQueue)
{
    (void)base;
    (void)parsed_command;
    (void)respQueue;
    Client *client = parsed_command.first;

    if (!motdInit)
        initMOTD();
    /*if (MOTDLines.empty())
        pushToQueue(client->_fd, CodeBuilder::errorToString(ERR_NOMOTD, this, client, &base), respQueue);*/
    else
    {
        pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_MOTDSTART, this, client, &base), respQueue);
        for (std::vector<std::string>::iterator it(MOTDLines.begin()); it != MOTDLines.end(); ++it)
        {
            pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_MOTD, this, client, &base), respQueue);
        }
        pushToQueue(client->_fd, CodeBuilder::errorToString(RPL_ENDOFMOTD, this, client, &base), respQueue);
        return true;
    }

    return (true);
}
