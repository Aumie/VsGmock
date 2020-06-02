#pragma once
#include <string>

class TryMock
{
public:
	class DataBaseConnect
	{
	public:
		virtual bool login(std::string usrname) { return true; }
		virtual bool logout(std::string usrname) { return true; }
		virtual int fetchRecord() { return -1; }
	};
	class MyDatabase
	{
		DataBaseConnect& dbc;
		
	};
};

