#pragma once
#include"GameSession.h"
#include"Database.h"
#include<cstdio>

const size_t BUFF_SIZE = 64;

class System
{
private:
	Database* database;
	GameSession* gameSession;
	
public:
	void activate();
	void systemHelp();
	void userHelp();
};

