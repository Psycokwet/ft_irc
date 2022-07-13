#ifndef FT_IRC_HPP
#define FT_IRC_HPP

#include <string>
#include <iostream>
#include <cstdlib>      // atoi
#include <sys/select.h> // select FD_CLR, FD_ZERO, FD_SET, FD_ISSET macros
#include <map>
#include <vector>
#include <set>
#include <list>
#include <iomanip> // setw, setfill

#include <unistd.h> // close
#include <sys/types.h>
#include <sys/socket.h> //socket accept listen send recv bind connect setsockopt getsockname
#include <netinet/in.h> // sockaddr_in

#include "../srcs/util/parse.hpp" //parsing

#include "code.hpp" //code command
#define DEFAULT_NAME "*"
#define MOTD_FILE "motd"

#define MAX_TCP_PORT 65535
#define TRUE 1

#define TOO_MANY_ARGS ": Too many params"
#define HOST "ourirc.42.paris.fr"
#define END_OF_COMMAND "\r\n"
#define LEN_END_OF_COMMAND 2

#define DEFAULT_NAME "*"

#define MAX_CLIENTS 25
#define MAX_CLIENT_QUEUE 3
#define BUF_SIZE 1000
#define FD_MAX 50 // number of fd we want to handle at a time
#define MAX(x, y) ((x > y) ? x : y)

#define SERVER_NAME "ourirc"
#define SERVER_VERSION "1.0.0"
#define SERVER_CREATION_DATE "07/07/2022"

typedef std::pair<int, std::string> t_clientCmd; // it: fd client, string: command

std::string getCodeWithZero(unsigned int n, int width);

#endif
