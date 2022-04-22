#include "Database.h"

const size_t BUFF_SIZE = 1024;

void secureFile(const char* fileName)
{
	std::ofstream file(fileName, std::ios::app);
	if (!file.is_open())
	{
		throw std::exception("Error! Could not access file!");
	}
}


Database::~Database()
{
	delete loggedIn;
	size_t usersCount = users.size();
	for (size_t i = 0; i < usersCount; i++)
	{
		delete users[i];
	}
}


User* Database::findUserByEmail(const String& searched)
{
	size_t usersCount = users.size();
	for (size_t i = 0; i < usersCount; i++)
	{
		if (users[i]->getEmail() == searched)
			return users[i];
	}
	return nullptr;
}

User* Database::findUserByUsername(const String& searched)
{
	size_t usersCount = users.size();
	for (size_t i = 0; i < usersCount; i++)
	{
		if (users[i]->getUsername() == searched)
			return users[i];
	}
	return nullptr;
}


const String& Database::getCurrentUser() const
{
	return loggedIn->getUsername();
}


void Database::registerUser()
{
	bool success = false;
	while (!success)
	{
		std::cout << "To register, type in your creditentials in the following format: \"email\" \"username\" \"password\"";
		std::cout << std::endl << "---> ";
		String email, username, password;
		std::cin >> email >> username >> password;
		if (findUserByEmail(email) != nullptr)
		{
			std::cout << "Error! User with that email address already exists!" << std::endl;
		}
		else if (findUserByUsername(email) != nullptr)
		{
			std::cout << "Error! User with that username already exists!" << std::endl;
		}
		else
		{
			users.push_back(new User(email, username, password, 0));
			success = true;
		}

	}
}

void Database::logIn()
{
	std::cout << "Please enter your username and password separated by a \" \" ---> ";
	String user, password;
	std::cin >> user >> password;

	User* login = findUserByUsername(user);

	if (login == nullptr)
		throw std::exception("Could not find username in the system!");

	else if (login->getPassword() != password)
		throw std::exception("Incorrect password!");

	else
	{
		std::cout << "Login successfull!" << std::endl;
		loggedIn = login;
	}
}

void Database::forgotPassword()
{
	bool success = false;
	while (!success)
	{
		std::cout << "Please, input your username and email ---> ";
		String user, email;
		std::cin >> user >> email;
		User* temp = findUserByUsername(user);
		if (temp == nullptr)
			std::cout << "Invalid username!" << std::endl;
		else if (temp->getEmail() != email)
			std::cout << "Email and username do not match!" << std::endl;
		else
		{

			std::cout << "Input new password and confirm it a second time ---> ";
			String pass1, pass2;
			std::cin >> pass1 >> pass2;
			while (!(pass1==pass2))
			{
				std::cout << "Passwords did not match! Try again ---> ";
				std::cin >> pass1 >> pass2;
			}
			std::cout << "password sucessfully changed!";
		}
			
	}
}

void Database::loadDatabase()
{
	try
	{
		secureFile("users.hangman");
	}
	catch (std::exception e)
	{
		throw e;
	}

	std::ifstream file("users.hangman");
	if (!file.is_open())
		throw std::exception("Error! Could not access database file!");

	size_t currUser = 0;
	while (!file.eof())
	{
		String email;
		String username;
		String password;
		size_t wins;

		file >> email >> username >> password >> wins;

		users.push_back(new User(email, username, password, wins));
	}

	std::cout << "Database successfully loaded!";
}

void Database::saveDatabase()
{
	std::ofstream file("users_temp.hangman");
	if (!file.is_open())
	{
		throw std::exception("An error occurred while trying to create the temp file for game!");
	}
	size_t usersCount = users.size();
	for (size_t i = 0; i < usersCount; i++)
	{
		file << users[i]->getEmail() << ' ' << users[i]->getUsername() << ' ';
		file << users[i]->getPassword() << ' ' << users[i]->getWins() << std::endl;
	}
	
	try
	{
		secureFile("users.hangman");
	}
	catch (std::exception e)
	{
		throw e;
	}

	int state = remove("users.hangman");
	if (state != 0)
		throw std::exception("Error! Could not delete old database file!");

	state = rename("users_temp.hangman", "users.hangman");
	if(state != 0)
		throw std::exception("Error! Could not rename temp file! Close any files from the game directory!");

	std::cout << "Database successfully saved!";
}

void Database::showLeaderboard()
{
	;
}

void Database::addWordToBank()
{
	WordBank::addNewWord();
}
