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

Channel::Channel( const Channel & src )
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Channel::~Channel()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Channel &				Channel::operator=( Channel const & rhs )
{
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Channel const & i )
{
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

//check channel prefix start = #

bool Channel::check_channel_prefix(char c)
{
    static std::string const prefix("#");
    return (prefix.find(c) != std::string::npos);
}

//check channel name 

bool Channel::check_channel_name(std::string const &name)
{
    static std::string const error_char("\a,: ");
    static std::set<char> const error_char_set(error_char_set.begin(), error_char_set.end());

    if (!check_channel_prefix(name[0]))
        return false;

    std::set<char> name_set(name.begin() + 1, name.end());
    std::vector<char> error(error_char.size());

    std::vector<char>::iterator	it(
        std::set_intersection(
			error_char_set.begin(), error_char_set.end(),
			name_set.begin(), name_set.end(),
			error.begin())
    );
    return std::distance(error.begin(), it) == 0;
}


int	Channel::addUser(User *user, std::string const &key)
{
	if (isUser(user))
		return -1;
	if (_userInvit && !isInvited(user))
		return ERR_INVITEONLYCHAN;
    if (isKey() && key != _key)
		return ERR_BADCHANNELKEY;
	_user.insert(user);
	_inv.erase(user);
	return 0;
}

bool Channel::isUser(User *user) const { return _user.find(user) != _user.end(); }
bool Channel::isInvited(User *user) const{ return (_inv.find(user) != _inv.end()); }
bool Channel::isKey() const {return !_key.empty();}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */