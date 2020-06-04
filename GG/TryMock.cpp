#include "TryMock.h"


int MyDatabase::init(std::string usrname, std::string pwd)
{
	if (!dbc.login(usrname, pwd))
	{
		std::cout << "DB FAILURE\n";
		return -1;
	}
	std::cout << "DB SUCCESS\n";
	return 1;
}