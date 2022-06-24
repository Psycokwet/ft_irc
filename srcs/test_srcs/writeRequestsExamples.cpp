
#include "../util/logger.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "What the pony am i supposed to do without a folder name ?" << std::endl;
		return -1;
	}
	std::string folder_name = av[1];

	gen_file_logger(folder_name + "QUIT.txt", "QUIT :Leaving\r\n");
	gen_file_logger(folder_name + "JOIN_services.txt", "JOIN #services\r\n");
	gen_file_logger(folder_name + "MODE.txt", "MODE #hackbbs\r\n");
	gen_file_logger(folder_name + "WHO.txt", "WHO #hackbbs\r\n");
	gen_file_logger(folder_name + "JOIN_hackbbs.txt", "JOIN #hackbbs\r\n");
	gen_file_logger(folder_name + "PRIVMSG_charlie_gnarly.txt", "PRIVMSG charlie_gnarly :hello\r\n");
	gen_file_logger(folder_name + "PRIVMSG_new_channel.txt", "PRIVMSG #new_channel :bla bla\r\n");
	return 0;
}