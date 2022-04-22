#pragma once
#include"String.h"
class User
{
private:
	String email;
	String username;
	String password;
	size_t wins;
	
public:
	User(String, String, String, size_t);

	String getUsername() const;
	String getPassword() const;
	String getEmail() const;
	size_t getWins() const;

	void setPassword(const String&);
	void addWin(const size_t&);
};