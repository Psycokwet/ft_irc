#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>

#define GREEN	"\e[0;32m"
#define NC		"\e[0m"

static inline void log_time(const std::string &message)
{
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H: %M:%S", timeinfo);
    std::string str(buffer);
    (void)message;
    std::cout << " [" << str << "] " << GREEN  << message << NC << std::endl;

};

#endif