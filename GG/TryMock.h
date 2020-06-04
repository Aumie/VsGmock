#pragma once
#include <iostream>
#include <string>
class DataBaseConnect
{
public:
	virtual bool login(std::string usrname, std::string	pwd) { return true; }
	virtual bool logout(std::string usrname) { return true; }
	virtual int fetchRecord() { return -1; }
};

class MyDatabase
{
	DataBaseConnect& dbc;
public:
	MyDatabase(DataBaseConnect& _dbc) : dbc(_dbc){}

	int init(std::string usrname, std::string pwd);
	
};


