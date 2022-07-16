
#include "../util/logger.hpp"
#include <sstream>
#define SSTR(x) static_cast<std::ostringstream &>(            \
					(std ::ostringstream() << std::dec << x)) \
					.str()

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "What the pony am i supposed to do without a folder name ?" << std::endl;
		return -1;
	}
	std::string folder_name = av[1];
	int i = 0;
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "TOPIC #chan\r\n"); 
	// :ft-irc.42.fr 331 meo #chanchan :No topic is set\r\n
	// appears on Hexchat

	// :luna.AfterNET.Org 332 meo #cha :xxx\r\n
    //  :luna.AfterNET.Org 333 meo #cha nnhung2!nnhung2@AN-89A16EB4.w90-92.abo.wanadoo.fr 1657918408\r\n
	// appears on Hexchat

	// all users can do this on existing channel. won't appear message if user does not belong to that channel.


	gen_file_logger(folder_name + SSTR(i++) + ".txt", "TOPIC #lajel\r\n");
	// :ft-irc.42.fr 482 nnhung2 #chanchan :You're not channel operator\r\n
	// appears on Hexchat

	// :ft-irc.42.fr 403 nnhung2 #balkdj :No such channel\r\n
	// not appeare on Hexchat

	gen_file_logger(folder_name + SSTR(i++) + ".txt", "TOPIC #chan :toptop tik tik\r\n");
	// :ft-irc.42.fr 482 nnhung2 #chanchan :You're not channel operator\r\n
	// appears on Hexchat

	// :meo!nnhung2@user.ft-irc.42.fr TOPIC #chanchan :tiktok\r\n
	// appears on Hexchat (sent to all clients on that channel)


	gen_file_logger(folder_name + SSTR(i++) + ".txt", "TOPIC #chan ::toptop\r\n");

	gen_file_logger(folder_name + SSTR(i++) + ".txt", "TOPIC #chan ::\r\n");

	gen_file_logger(folder_name + SSTR(i++) + ".txt", "LIST\r\n");

	// :luna.AfterNET.Org 321 nnhung2 Channel :Users  Name\r\n
	// :luna.AfterNET.Org 322 nnhung2 #lovenation 10 :Channel's topic\r\n
	// :luna.AfterNET.Org 323 nnhung2 :End of /LIST\r\n

	return 0;
}