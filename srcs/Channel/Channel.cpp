#include "Channel.hpp"
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Channel::Channel(std::string const &name, Users *create) :
    _name(name), _userInvit(false), _nottopic(false)
{
    _op.insert(create);
    _users.insert(create);
}
/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
Channel::~Channel(){}
