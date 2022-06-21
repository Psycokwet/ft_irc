#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
#include "../User/User.hpp"
#include "../../includes/ft_irc.hpp"
#include "../../includes/code.hpp"

class Channel
{
	public:

		Channel(const std::string &name, User *create);
		Channel( Channel const & src );
		virtual ~Channel();

		Channel &		operator=( Channel const & rhs );

		static bool check_channel_prefix(char c);
    	static bool check_channel_name(std::string const &name);
		int addUser(User *user, std::string const &key);

		bool isUser(User *user) const;
   		bool isInvited(User *user) const;
    	bool isKey() const;

	private:

	std::string const _name; //nom du channell
    std::set<User *> _user; //liste des users inscrit
    std::string     _topic; //sujet de la channel

    bool _userInvit;//seulement les user inscrit
    bool _nottopic;//no subjet

    std::set<User *> _op; //liste operateur
    std::string _key; //clee channel
    std::set<User *> _inv; //liste des user invitee

};

std::ostream &			operator<<( std::ostream & o, Channel const & i );

#endif /* ********************************************************* CHANNEL_H */