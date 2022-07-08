#ifndef ClientMode_HPP
#define ClientMode_HPP

#include <iostream>
#include <string>
#define _MOD_FLAG_ADMIN 1
class ClientMode
{

public:
	ClientMode(int flags = 0);
	~ClientMode();

private:
	ClientMode &operator=(ClientMode const &rhs);
	ClientMode(ClientMode const &src);
	int _flags;
};

#endif /* *********************************************** ClientMode_H */