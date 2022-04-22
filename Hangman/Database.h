#pragma once
#include"User.h"
#include"WordBank.h"
#include<fstream>
#include<iostream>
#include<vector>
class Database
{
private:
	std::vector<User*> users;
	User* loggedIn;

public:
	Database(const Database&) = delete;
	const Database& operator=(const Database&) = delete;
	~Database();

	User* findUserByEmail(const String&);
	User* findUserByUsername(const String&);

	const String& getCurrentUser() const;

	void registerUser();
	void logIn();
	void forgotPassword();
	void loadDatabase();
	void saveDatabase();
	void showLeaderboard();
	void addWordToBank();
};

