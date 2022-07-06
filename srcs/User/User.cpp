#include "User.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
User::User(int fd) : _fd(fd),
					 _passOK(false)
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

int User::get_fd() const
{
	return (_fd);
}
