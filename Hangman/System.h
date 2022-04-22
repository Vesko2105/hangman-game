#pragma once
#include"GameSession.h"
#include"Database.h"

const size_t BUFF_SIZE = 64;

class System
{
private:
	Database* database;
	GameSession* gameSession;
	
public:
	void activate();
};

