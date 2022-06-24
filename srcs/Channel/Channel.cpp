#include "Channel.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel(std::string const &name, User *create) : _name(name), _invit(false), _nottopic(false)
{
	_op.insert(create);
	_user.insert(create);
}

Channel::Channel(const Channel &src)
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

Channel &Channel::operator=(Channel const &rhs)
{
	// if ( this != &rhs )
	//{
	// this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Channel const &i)
{
	// o << "Value = " << i.getValue();
	return o;
}
/*
** --------------------------------- METHODS ----------------------------------
*/

// check channel prefix start = #

bool Channel::check_channel_prefix(char c)
{
	static std::string const prefix("#");
	return (prefix.find(c) != std::string::npos);
}

// check channel name

bool Channel::check_channel_name(std::string const &name)
{
	static std::string const error_char(ERROR_CHAR);
	static std::set<char> const error_char_set(error_char_set.begin(), error_char_set.end());

	if (!check_channel_prefix(name[0]))
		return false;

	std::set<char> name_set(name.begin() + 1, name.end());
	std::vector<char> error(error_char.size());

	std::vector<char>::iterator it(
		std::set_intersection(
			error_char_set.begin(), error_char_set.end(),
			name_set.begin(), name_set.end(),
			error.begin()));
	return std::distance(error.begin(), it) == 0;
}

int Channel::addUser(User *user, std::string const &key)
{
	if (isUser(user))
		return -1;
	if (_invit && !isInvited(user))
		return ERR_INVITEONLYCHAN;
	if (isKey() && key != _key)
		return ERR_BADCHANNELKEY;
	_user.insert(user);
	_userInv.erase(user);
	return 0;
}

bool Channel::isUser(User *user) const { return _user.find(user) != _user.end(); }
bool Channel::isInvited(User *user) const { return (_userInv.find(user) != _userInv.end()); }
bool Channel::isKey() const { return !_key.empty(); }
bool Channel::isOp(User *user) const { return (_op.find(user) != _op.end()); }

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

//  MODE #channel +modeshere.
int Channel::setChannelMode(IRCServer *IRCServer, bool plus, char mode, std::string const &param)
{
	static std::string everyModes(EVERY_MODE);
	static std::string validModes(VALID_MODE);

	if (everyModes.find(mode) == std::string::npos)
		return ERR_UNKNOWNMODE;
	if (mode == 't' && plus == _nottopic)
	{
		_nottopic = !_nottopic;
		return 0;
	}
	if (mode == 'k' && isKey() && !plus) // -k
	{
		if (param == _key)
			_key = "";
		return (param != _key) * ERR_KEYSET;
	}
	if (mode == 'k' && !isKey() && plus) // +k
	{
		_key = param;
		return 0;
	}
	if (mode == 'i' && plus != _invit)
	{
		_invit = !_invit;
		return 0;
	}
	if (mode == 'o')
	{
		User *target(IRCServer->getUserByNick(param));
		if (!target)
			return ERR_NOSUCHNICK;
		else if (plus && isInvited(target) && !isOp(target))
		{
			_op.insert(target);
			return 0;
		}
		else if (!plus && isOp(target))
		{
			_op.erase(target);
			return 0;
		}
	}
	return -1;
}

std::string Channel::getChannelMode() const
{
	std::string mode("+");
	if (_invit)
		mode += 'i';
	if (!_key.empty())
		mode += 'k';
	if (!_nottopic)
		mode += 't';
	return mode;

	/* ************************************************************************** */
