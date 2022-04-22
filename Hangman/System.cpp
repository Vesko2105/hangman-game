#include "System.h"

void System::activate()
{
	database = new Database();
	String command;
	while (true)
	{
		std::cout << "Enter a command (or type 'help' to see the list of commands)..." << std::endl;
		std::cout << "> ";
		command.getline(std::cin, BUFF_SIZE);

		if (command == "help")
		{
			systemHelp();
		}

		else if (command == "register")
		{
			try
			{
				database->registerUser();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what();
			}
		}

		else if (command == "login")
		{
			try
			{
				database->logIn();
				std::cin.ignore();

				while (true)
				{
					std::cout << "Enter a command (or type 'help' to see the list of commands)..." << std::endl;
					std::cout << "> ";
					command.getline(std::cin, BUFF_SIZE);

					if (command == "game menu")
					{
						gameSession->enterGameMenu(database->getCurrentUser());
					}
					else if (command == "leaderboard")
					{
						database->showLeaderboard();
					}
					else if (command == "submit word")
					{
						std::cout << "Enter the word you woyld like to submit:";
						String word;
						std::cin >> word;
						std::cout << "Are you sure you want to submit the word '" << word << "'? [Y/N]";
						std::cin >> command;
						if (command == "Y")
							database->addWordToBank(word);
						else
							std::cout << "Submitting canceled." << std::endl;
					}
					else if (command == "help")
					{
						userHelp();
					}
					else if (command == "log out")
					{

						break;
					}
					else
					{
						std::cout << "Invalid command!" << std::endl;
					}
				}
				std::cout << std::endl << "Logged out successfuly!" << std::endl << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		else if (command == "forgot password")
			database->forgotPassword();

		else if (command == "exit")
			break;

		else
			std::cout << "Invalid command!" << std::endl << std::endl;
	}
	std::cout << std::endl << "System closed successfully! Goodbye!" << std::endl;
}

void System::systemHelp()
{
	std::cout << std::endl
			<< "------------------------------Commands------------------------------\n"
			<< "| register - Allows a new user to register in the system           |\n"
			<< "| login - Allows an existing user to log into his account          |\n"
			<< "| forgot password - Allows an axisting user to recover his acount  |\n"
			<< "| exit - exit the system                                           |\n"
			<< "| help - reveals a list of possible commands                       |\n"
			<< "--------------------------------------------------------------------\n"
			<< std::endl;
}

void System::userHelp()
{
	std::cout << std::endl
		<< "------------------------------Commands------------------------------\n"
		<< "| play - Opens the game menu                                       |\n"
		<< "| leaderboard - Shows the current leaderboard                      |\n"
		<< "| submit word - Allows the user to submit a word to the word bank  |\n"
		<< "| logout - Loggs out the user from the system                      |\n"
		<< "| help - reveals a list of possible commands                       |\n"
		<< "--------------------------------------------------------------------\n"
		<< std::endl;
}
