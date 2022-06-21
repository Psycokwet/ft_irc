#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include "../User/User.hpp"
#include "../../includes/ft_irc.hpp"
#include "../../includes/code.hpp"

class Channel
{
    private:

    std::string const _name; //nom du channell

    std::set<User *> _user; //liste des users inscrit

    std::string     _topic; //sujet de la channel

    bool _userInvit;//seulement les user inscrit
    bool _nottopic;//no subjet
    std::set<User *> _op; //liste operateur
    std::string _key; //clee channel
    std::set<User *> _inv; //liste des user invitee


    public:

    static bool check_channel_prefix(char c);
    static bool check_channel_name(std::string const &name);

    Channel(const std::string &name, User *create);
    virtual ~Channel();

    int addUser(User *user, std::string const &key);

    bool isUser(User *user) const;
    bool isInvited(User *user) const;
    bool isKey() const;

    


};







#endif