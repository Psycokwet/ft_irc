#ifndef FT_IRC_HPP
# define FT_IRC_HPP

#include <string>
#include <iostream>
#include <cstdlib> // atoi
#include <sys/select.h> // FD_CLR, FD_ZERO, FD_SET, FD_ISSET macros
#include <map>

#include <sys/types.h>         
#include <sys/socket.h> //socket accept listen send recv bind connect setsockopt getsockname
# include <sys/select.h> //select

#define MAX_TCP_PORT 65535
#define TRUE 1



#define MAX_CLIENTS 25
#define MAX_CLIENT_QUEUE 3
#define BUF_SIZE 100000
#define FD_MAX 50 // number of fd we want to handle at a time
#define MAX(x, y) ((x > y) ? x : y) 

#endif