#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include "../Users/Users.hpp"
#include "../../../includes/ft_irc.hpp"

class Channel
{
    private:

    std::string const _name; //nom du channell

    std::set<User *> _user; //liste des users inscrit

    std::string     _topic; //sujet de la channel

    bool _userInvit;//seulement les joueur inscrit
    bool _nottopic;//no subjet
    std::set<User *> _op; //liste operateur
    std::string _key; //clee channel

    std::set<User *> _inv; //liste des user invitee


    public:

    Channel(const std::string &name, User *create);
    virtual ~Channel();

    //int checkAddUsers(Users *users, std::string const &key);


};







#endif