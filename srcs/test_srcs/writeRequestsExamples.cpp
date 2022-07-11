
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
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "PING 1657489741146\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "PASS abc\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "QUIT :Leaving\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "JOIN #services\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "MODE #hackbbs\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "WHO #hackbbs\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "JOIN #hackbbs\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "PRIVMSG charlie_gnarly :hello\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "PRIVMSG #new_channel :bla bla\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "WHO #new_channel\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "PART #new_channel :I quit\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "JOIN #new_channel\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "PRIVMSG thi-nguy :hello\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "NAMES #new_channel\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "NAMES #new_channel,#other_channel\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "KICK #new_channel thi-nguy :Speaking_English\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "MODE #new_channel meo +i\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "NICK thi-nguy\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "USER thi-nguy 0 * :realname\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "PING LAG1657476314910\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "PING :irc.funet.fi\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "PING WiZ tolsun.oulu.fi\r\n");
	gen_file_logger(folder_name + SSTR(i++) + ".txt", "NOTICE thi-nguy :PING 1657491395742\r\n"); // this is sent when we click on the button "PING" on Hexchat
	return 0;
}