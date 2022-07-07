#include "User.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
User::User(int fd) : _fd(fd),
                     _passOK(false),
                     _uname(DEFAULT_NAME)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

User::~User()
{
}

/*
** --------------------------------- PUBLIC METHODS ---------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/
bool User::getRegistered() const
{
    return (_registered);
}
void User::SetNick(std::string const &nick)
{
    _nick = nick;
    if (_uname != DEFAULT_NAME)
        getRegistered();
}
void User::SetUsername(const std::string &uname)
{
    _uname = uname;
    if (_nick != DEFAULT_NAME)
        getRegistered();
}
