#include "System.h"

void System::activate()
{
	gameSession = new GameSession;
	String command;
	while (command != "exit")
	{
		std::cout << "Enter a command ---> ";
		char* temp = new char[BUFF_SIZE];
		std::cin.getline(temp, BUFF_SIZE);
		command = temp;

		if (command == ">register")
			database->registerUser();

		else if (command == ">login")
		{
			try
			{
				database->logIn();

				std::cout << "Type in a command from the list:" << std::endl;
				std::cout << ">game menu to enter the game menu" << std::endl;
				std::cout << ">leaderboard to see the leaderboard" << std::endl;
				std::cout << ">add word to submit a word to the word bank" << std::endl;
				std::cout << ">log out to log out of your account" << std::endl;
				while (command != ">log out")
				{
					std::cout << "---> ";
					while (command != ">game menu" && command != ">leaderboard" && command != ">add word" && command != ">log out")
					{
						std::cout << "Invalid command!" << std::endl;
						std::cout << "---> ";
						std::cin.getline(temp, BUFF_SIZE);
						command = temp;
					}
					if (command == ">game menu")
					{
						gameSession->enterGameMenu(database->getCurrentUser());
					}
					else if (command == ">leaderboard")
					{
						database->showLeaderboard();
					}
					else if (command == ">add word")
					{
						database->addWordToBank();
					}
				}
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		else if (command == ">forgot password")
			database->forgotPassword();

		else if (command == ">addword")
			;

		command = '\0';
	}
	std::cout << "System closed successfully!";
}
