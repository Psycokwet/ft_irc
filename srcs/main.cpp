#include "../includes/ft_irc.hpp"
#include "network/MasterServer.hpp"


MasterServer *gMasterServer = NULL; 

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

static void	cleanup()
{
	if (gMasterServer)
		delete gMasterServer;
}

static void	handleSignal(int signum)
{
	if (signum == SIGINT) // hit Ctr + C
		std::cout << "\nServer stopped. Good bye!\n" << std::endl;
	exit(0);
}

int main(int ac, char **av)
{
	std::atexit(cleanup);
	signal(SIGINT, handleSignal);

	int port;
	std::string password;

	if (!checkArguments(ac, av, port, password))
		exit(1);

	gMasterServer = new MasterServer(port, password);

	if (gMasterServer->build() == EXIT_FAILURE)
	{
		delete gMasterServer;
		return (1);
	}
	gMasterServer->run();
	return (0);
}