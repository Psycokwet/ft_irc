#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include "../Users/Users.hpp"
#include "../../../includes/ft_irc.hpp"

class Channel
{
    private:

    std::string const _name; //nom du channell

    std::set<Users *> _users; //liste des users inscrit

    std::string     _topic; //sujet de la channel

    bool _userInvit;//seulement les joueur inscrit
    bool _nottopic;//no subjet
    std::set<Users *> _op; //liste operateur
    std::string _key; //clee channel

    std::set<Users *> _inv; //liste des user invitee


    public:

    Channel(const std::string &name, Users *create);
    virtual ~Channel();

    //int checkAddUsers(Users *users, std::string const &key);


};







#endif