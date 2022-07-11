
#include "../util/logger.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#define SSTR(x) static_cast<std::ostringstream &>(            \
					(std ::ostringstream() << std::dec << x)) \
					.str()

int main(int ac, char **av)
{
	if (ac < 3)
	{
		std::cerr << "What the pony am i supposed to do without a file name and folder name ?" << std::endl;
		return -1;
	}
	std::string scenario_filename = av[1];
	std::ifstream ifs(scenario_filename.c_str());
	std::string tmp_line = "";
	std::stringstream ss;
	std::string folder_name = av[2];
	int i = 0;
	std::string base_filename = scenario_filename.substr(scenario_filename.find_last_of("/\\") + 1);
	while (std::getline(ifs, tmp_line))
	{
		gen_file_logger(folder_name + base_filename + "/" + SSTR(i++) + ".txt", tmp_line + "\r\n");
	}
	return 0;
}