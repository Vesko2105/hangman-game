#include "GameSession.h"

const size_t BUFF_SIZE = 128;

GameSession::GameSession():
	currentGame(nullptr)
{
	;
}

void GameSession::createNewGame(const String& word)
{
	if (currentGame != nullptr)
		throw std::exception("A game has already been started!");
	currentGame = new Game(word);
}

void GameSession::loadSavedGame(const String& fileName)
{
	if (currentGame != nullptr)
		throw std::exception("A game has already been started!");

	std::ifstream file(fileName.getData());
	if (!file.is_open())
		throw std::exception("Error! File could not be accessed!");

	size_t boardPhase;
	size_t turnsPassed;
	String wordToGuess;
	String wordToDisplay;
	String guessedLetters;
	String alphabet;

	file >> boardPhase;
	file >> turnsPassed;
	file >> wordToGuess;
	file >> wordToDisplay;
	file >> guessedLetters;

	char* buff = new char[BUFF_SIZE];
	file.getline(buff, BUFF_SIZE);
	alphabet = buff;
	delete[] buff;

	currentGame = new Game(boardPhase, turnsPassed, wordToGuess, wordToDisplay, guessedLetters, alphabet);
}

void GameSession::saveGame(const String& user)
{
	currentGame->saveToFile(user);
	delete currentGame;
	currentGame = nullptr;
}

void GameSession::enterGameMenu(const String& user)
{
	String command;
	while (command != "exit")
	{
		std::cout << "Type \"start new game\" to create a new game, \"load game\" to load an existing save or \"exit\" to exit the game menu ---> ";
		char* buff = new char[BUFF_SIZE];
		std::cin.getline(buff, BUFF_SIZE);
		command = buff;
	
		while (command != "load game" && command != "start new game" && command != "exit")
		{
			std::cout << "Error! Invalid command! Input a command from the list above ---> ";
			delete[] buff;
			buff = new char[BUFF_SIZE];
			std::cin.getline(buff, BUFF_SIZE);
			command = buff;
		}

		if (command == "start new game")
		{
			createNewGame("");
			startGame(user);
		}

		else if (command == "load")
		{
			bool flag = false;
			while (!flag)
			{
				std::cout << "Enter the full name of the game file ---> ";
				String fileName;
				std::cin.getline(buff, BUFF_SIZE);
				fileName = buff;
				try
				{
					loadSavedGame(fileName);
					flag = true;
				}
				catch (const std::exception& e)
				{
					std::cout << e.what();
					flag = false;
				}
			}
			startGame(user);
		}
	}
}

void GameSession::startGame(const String& user)
{
	while (currentGame->getState() == Ongoing)
	{
		try
		{
			currentGame->makeTurn();
		}
		catch (std::exception e)
		{
			std::cout << e.what();
		}
	}

	if (currentGame->getState() == OnHold)
	{
		saveGame(user);
	}

	else if (currentGame->getState() == Loss)
	{
		std::cout << "You Got Hanged" << std::endl;
		std::cout << "The correct word was \"" << currentGame->getWordToGuess() << "\"";
	}

	else
	{
		std::cout << "Congratulations! You Saved Your Skin!";
	}
}
