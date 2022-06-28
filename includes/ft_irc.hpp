#ifndef FT_IRC_HPP
#define FT_IRC_HPP

#include <string>
#include <iostream>
#include <cstdlib>		// atoi
#include <sys/select.h> // select FD_CLR, FD_ZERO, FD_SET, FD_ISSET macros
#include <map>
#include <vector>
#include <set>

#include <unistd.h> // close
#include <sys/types.h>
#include <sys/socket.h> //socket accept listen send recv bind connect setsockopt getsockname
#include <netinet/in.h> // sockaddr_in

#include "../srcs/util/parse.hpp" //parsing

#define MAX_TCP_PORT 65535
#define TRUE 1

#define MAX_CLIENTS 25
#define MAX_CLIENT_QUEUE 3
#define BUF_SIZE 1000
#define FD_MAX 50 // number of fd we want to handle at a time
#define MAX(x, y) ((x > y) ? x : y)

typedef std::pair<int, std::string> t_clientCmd; // it: fd client, string: command

typedef std::pair<int, lazyParsedType *> t_client_ParsedCmd; // it: fd client, lazyParsedType: parsed command
#endif