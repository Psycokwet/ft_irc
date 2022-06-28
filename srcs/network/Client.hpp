#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "MasterServer.hpp"

#include "../../includes/ft_irc.hpp"

#define END_OF_COMMAND "\r\n"
#define LEN_END_OF_COMMAND 2

class Client
{
public:
	friend class MasterServer;

private:
	int _fd;
	char _buffer[BUF_SIZE + 1];
	std::string _commandTemp;

	Client();
	Client(int fd);
	bool receiveCommand(std::string &command);
	void sendResp(std::string const &resp);
};

#endif