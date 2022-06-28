#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <string>
#include "../../includes/ft_irc.hpp"
#include "../Channel/Channel.hpp"

class User
{

public:
	User(int fd);
	User(User const &src);
	virtual ~User();

	User &operator=(User const &rhs);

	void setNickname(const std::string &nickname);
	void setUsername(const std::string &username);
	void setRealName(const std::string &realname);

	std::string getNickname() const;
	std::string getUsername() const;
	std::string getRealName() const;

	friend class IRCServer;

private:
	int _fd;
	bool _passOK;
	bool _log;

	std::string _nickName;
	std::string _userName;
	std::string _realName;
	std::string _prefixUser;

	std::set<Channel *> _add; // list channel user add

	// USER MODE
	std::string _Msg;
	bool _invisible; // (i) Is invisible
	bool _op;		 // (o) Is server operator

protected:
	User(int fd, std::string const &origin);
	void registrationOK();
};

std::ostream &operator<<(std::ostream &o, User const &i);

#endif /* ************************************************************ USER_H */