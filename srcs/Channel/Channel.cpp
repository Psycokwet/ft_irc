#include "Channel.hpp"
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Channel::Channel(std::string const &name, User *create) :
    _name(name), _userInvit(false), _nottopic(false)
{
    _op.insert(create);
    _user.insert(create);
}
/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
Channel::~Channel(){}
