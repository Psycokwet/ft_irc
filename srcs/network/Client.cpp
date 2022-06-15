#include "Client.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Client::Client(int fd) :
    _fd(fd)
{}

/*
** ------------------------- PRIVATE METHODS ----------------------------------
*/

bool Client::receiveCommand(std::string &command)
{
    ssize_t r = recv(_fd, _buffer, BUF_SIZE, 0);
    if (r <= 0)
        return false;
    _buffer[r] = '\0';

    // ! Parsing here, getting value to `command`
    command += _buffer;

    return true;
}

void Client::sendResp(std::string const &resp)
{
    send(_fd, resp.c_str(), resp.size(), 0);
}
