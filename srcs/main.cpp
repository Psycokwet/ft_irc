#include "../includes/ft_irc.hpp"
#include "network/MasterServer.hpp"

static bool checkArguments(int ac, char **av, int &port, std::string &password)
{
    if (ac != 3)
    {
        std::cout << "Invalid Number of argument." << std::endl;
        return false;
    }
    else
    {
        port = std::atoi(av[1]);
        if (port <= 0 || port > MAX_TCP_PORT)
        {
            std::cout << "Invalid Port Number." << std::endl;
            return false;
        }
        password = std::string(av[2]);
    }
    return true;
}
int main (int ac, char **av)
{
    int port;
    std::string password;
    if (!checkArguments(ac, av, port, password))
        exit(1);
    
    IRCServer *myIrc = new IRCServer(password);
    MasterServer *myServer = new MasterServer(port, password, *myIrc);

    if (myServer->build() == EXIT_FAILURE)
    {
        delete myIrc;
        delete myServer;
        return (1);
    }
    myServer->run();
    return (0);
}