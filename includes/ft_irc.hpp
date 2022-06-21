#ifndef FT_IRC_HPP
# define FT_IRC_HPP

#include <string>
#include <iostream>
#include <cstdlib> // atoi
#include <set>
#include <map>
#include <vector>

#define MAX_TCP_PORT 65535
#define TRUE 1



#define MAX_CLIENTS 25
#define MAX_CLIENT_QUEUE 3
#define BUF_SIZE 1000
#define FD_MAX 50 // number of fd we want to handle at a time
#define MAX(x, y) ((x > y) ? x : y) 

#define DEFAULT_NAME	"*"
#define VALID_CHARS		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-^_[]{}\\|"
#define ERROR_CHAR      "\a,: "

#endif