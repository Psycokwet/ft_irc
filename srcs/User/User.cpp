#include "User.hpp"
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
User::User(int fd):
    _fd(fd), _passOK(false), _log(false), _nickName(DEFAULT_NAME),
    _userName(DEFAULT_NAME), _realName(DEFAULT_NAME)
    {}

User::User(int fd, std::string const &origin):
_fd(fd), _passOK(true), _log(true), _nickName(origin),
_userName(origin), _realName(origin)
{}
/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
User::~User()
{}