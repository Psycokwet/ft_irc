#include "User.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

User::User(int fd) : _fd(fd), _passOK(false), _log(false), _nickName(DEFAULT_NAME),
					 _userName(DEFAULT_NAME), _realName(DEFAULT_NAME)
{
}

User::User(int fd, std::string const &src) : _fd(fd), _passOK(true), _log(true), _nickName(src),
											 _userName(src), _realName(src)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

User::~User()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

User &User::operator=(User const &rhs)
{
	// if ( this != &rhs )
	//{
	// this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &operator<<(std::ostream &o, User const &i)
{
	// o << "Value = " << i.getValue();
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

// Check if user is currently idling away
bool User::IsAway() const
{
	return (!_awayMsg.empty());
}

bool User::IsVisible() const
{
	return (!_invisible);
}
bool User::IsUsernameDefault() const
{
	return (_userName == DEFAULT_NAME);
}
void User::registrationOK()
{
	_log = true;
	_prefixUser = std::string(":") + _nickName + '!' + _userName + '@' + USR_HOST;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string User::GetModes() const
{
	std::string mode("+");
	if (IsAway())
		mode += "a";
	if (_invisible)
		mode += "i";
	if (_op)
		mode += "o";
	return mode;
}

void User::setNickname(const std::string &nickname)
{
	_nickName = nickname;
	if (_userName != DEFAULT_NAME)
		registrationOK();
};

void User::setUsername(const std::string &username)
{
	_userName = username;
	if (_nickName != DEFAULT_NAME)
		registrationOK();
};
void User::setRealName(const std::string &realname) { _realName = realname; };

std::string User::getNickname() const { return _nickName; };
std::string User::getUsername() const { return _userName; };
std::string User::getRealName() const { return _realName; };

/* ************************************************************************** */
