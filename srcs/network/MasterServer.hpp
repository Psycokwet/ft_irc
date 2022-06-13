#ifndef MASTERSERVER_HPP
#define MASTERSERVER_HPP

#include "../../includes/ft_irc.hpp"
#include "Client.hpp"

class MasterServer
{
	public:
		MasterServer();
		MasterServer(const MasterServer &src);
		MasterServer &operator=(const MasterServer &rhs);
		~MasterServer();

		std::ostream &print_client_map(std::ostream &o) const;
		
		int build();
		void run();

		class AnError : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return "ERROR: ";
				}
		};

		void print_network_map() const;

    private:
        int				 					_fdServer;	// Server's socket
		std::map<int, Client*>				_clients;
        int									_maxFD;		// Current highest client FD
        fd_set								_fdReader;	// Structure to select client FD for reading

        void		acceptClient(int fdServer);
        void		setFDForReading();
        void		recvProcess(void);
};

#endif /*...................MasterServer...............*/