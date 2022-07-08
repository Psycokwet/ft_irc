/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainParserTest.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 22:03:00 by scarboni          #+#    #+#             */
/*   Updated: 2022/05/09 17:20:34 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../util/parse.hpp"
#include "../network/MasterServer.hpp"
#include <ctype.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>

int main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
	{
		std::cout << "I'm only a request parser for test, what do you expect by not giving me any file name to read from?" << std::endl;
		return 0;
	}

	std::ifstream ifs(av[1]);

	std::string tmp;
	std::string buff;
	while (std::getline(ifs, tmp))
	{
		buff += tmp + "\n";
	}

	MasterServer *myIrc = new MasterServer(4242, "password");
	lazyParsedType *lad = LazyRequestParser(buff);
	if (!lad)
	{
		std::cout << RED << "FAILURE\n"
				  << RESET;
		return -1;
	}
	std::cout << BLUE << "Parsed, original:\n"
			  << GREEN
			  << buff
			  << RESET;
	print_lazyrequest(std::cout, *lad);
	std::vector<t_clientCmd> empty;
	t_client_ParsedCmd testDatas = std::make_pair(0, lad);
	myIrc->processCommand(testDatas, empty);
	delete myIrc;
	return 0;
}