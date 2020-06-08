#include "TryMock.h"
#include <ctime>

int MyDatabase::init(std::string usrname, std::string pwd)
{
	srand(time(NULL));
	int rval = rand() % 2;
	if(!rval)
	{
		if (!dbc.login(usrname, pwd))
		{
			std::cout << "DB FAILURE\n";
			return -1;
		}
		std::cout << "DB SUCCESS\n";
		return 1;
	}
	return dbc.login2(usrname, pwd);
}
