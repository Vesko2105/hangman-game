#include "Database.h"

const size_t BUFF_SIZE = 1024;

void secureFile(const char* fileName)
{
	std::ofstream file(fileName, std::ios::app);
	if (!file.is_open())
	{
		throw std::exception("Error! Could not access file!");
	}
	file.close();
}


Database::Database()
{
	try
	{
		loadDatabase();
	}
	catch (const std::exception& e)
	{
		throw e;
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
	bool stop = false;
	while (!stop )
	{
		std::cout << "To register, type in your creditentials in the following format: 'email' 'username' 'password'" << std::endl;
		std::cout << "> ";
		String email, username, password, command;
		std::cin >> email >> username >> password;
		if (findUserByEmail(email) != nullptr)
		{
			throw std::exception("Error! User with that email address already exists!");
		}
		else if (findUserByUsername(email) != nullptr)
		{
			throw std::exception("Error! User with that username already exists!");
		}
		else
		{
			try
			{
				secureFile("users.hangman");
			}
			catch (const std::exception& e)
			{
				throw e;
			}

			users.push_back(new User(email, username, password, 0));

			std::ofstream usersFile;

			usersFile.open("users.hangman", std::ios::app);
			usersFile << users.back()->getEmail() << ' ' << users.back()->getUsername() << ' '
					  << users.back()->getPassword() << ' ' << users.back()->getWins() << std::endl;

			std::cout << std::endl << username << " registered successfuly!" << std::endl;
			stop = true;
		}
	}
}

void Database::logIn()
{
	std::cout << std::endl << "Please enter your username and password separated by an empty space:" << std::endl;
	std::cout << "> ";
	String username, password;
	std::cin >> username >> password;

	User* user = findUserByUsername(username);

	if (user == nullptr)
		throw std::exception("Could not find username in the system!");

	else if (user->getPassword() != password)
		throw std::exception("Incorrect password!");

	else
	{
		std::cout << std::endl << "Login successfull! Welcome " << username << '!' << std::endl << std::endl;
		loggedIn = user;
	}
}

void Database::forgotPassword()
{
	bool success = false;
	while (!success)
	{
		std::cout << "Please, input your username and email seperated by a space:" << std::endl;
		std::cout << ">";
		String user, email;
		std::cin >> user >> email;
		User* temp = findUserByUsername(user);
		if (temp == nullptr)
			std::cout << "Invalid username!" << std::endl;
		else if (temp->getEmail() != email)
			std::cout << "Email and username do not match!" << std::endl;
		else
		{
			String pass1, pass2;

			bool success = false;
			while (!success)
			{
				std::cout << "Input new password:" << std::endl;
				std::cout << ">";
				std::cin >> pass1;
				std::cout << "Confirm new password:" << std::endl;
				std::cout << ">";
				std::cin >> pass2;
				if (pass1 != pass2)
				{
					std::cout << "Passwords did not match!";
				}
				else
					success = true;
			}
			std::cout << "Password sucessfully changed!";
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

	while (!file.eof())
	{
		String email;
		String username;
		String password;
		size_t wins;

		file >> email >> username >> password >> wins;
		if (email == "")
			break;
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

void Database::addWordToBank(String& word)
{
	//addNewWord(word);
}
