#include "User.h"

const size_t BUFF_SIZE = 128;

User::User(String email, String user, String pass, size_t wins): 
	email(email), username(user), password(pass), wins(wins)
{
	;
}

String User::getUsername() const
{
	return username;
}

String User::getPassword() const
{
	return password;
}

String User::getEmail() const
{
	return email;
}

size_t User::getWins() const
{
	return wins;
}

void User::setPassword(const String& newPass)
{
	password = newPass;
}

void User::addWin(const size_t& x)
{
	wins++;
}

String User::toString()
{
	return String(email + " | " + password + " | " + username + " | " + (int)wins);
}
