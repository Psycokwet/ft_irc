#ifndef USER_HPP
#define USER_HPP


#include "../Channel/Channel.hpp"
#include "../../includes/ft_irc.hpp"

class User
{
    private:

    int _fd;
    bool _passOK;
    bool _log;

    std::string _nickName;
    std::string _userName;
    std::string _realName;
    std::string _prefixUser;

    std::set<Channel *> _add;//list channel user add


    std::string _Msg;
    bool	_invisible;		// (i) Is invisible
	bool	_oper;			// (o) Is server operator

    protected:
	User(int fd, std::string const &origin);
	void	registrationOK();

    public:

    User(int fd);
    virtual ~User();



    void setNickname(const std::string &nickname) { _nickName = nickname; };
    void setUsername(const std::string &username) { _userName = username; };
    void setRealName(const std::string &realname) { _realName = realname; };

    std::string getNickname() const { return _nickName; };
    std::string getUsername() const { return _userName; };
    std::string getRealName() const { return _realName; };




    




};

#endif