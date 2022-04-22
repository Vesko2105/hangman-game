#include "Game.h"

const size_t BUFF_SIZE = 1024;

//helper functions
void secureGameFile(const char* fileName)
{
	std::ofstream file(fileName, std::ios::app);
	if (!file.is_open())
	{
		throw std::exception("Error! Could not access file!");
	}
}

String generateFileName(const String& word, const String& user)
{
	String fileName;
	size_t x = 0;
	size_t wordLen = word.getSize() - 1;
	for (size_t i = 0; i < wordLen; i++)
	{
		x += word[i];
	}
	fileName = user + '_' + intToString(x) + ".hangman";
	return fileName;
}

String generateTempFile(const String& word, const String& user)
{
	String fileName;
	size_t x = 0;
	size_t wordLen = word.getSize() - 1;
	for (size_t i = 0; i < wordLen; i++)
	{
		x += word[i];
	}
	fileName = user + '_' + intToString(x) + "_temp" + ".hangman";
	return fileName;
}


Game::Game(const String& word):
	turnsPassed(0), wordToGuess(word), alphabet("A B C D E F G H I J K L M N O P Q R S T U V W X Y Z"), gameState(Ongoing)
{
	wordToDisplay = wordToGuess;
	size_t len = wordToDisplay.getSize() - 1;
	for (size_t i = 1; i < len-1; i++)
	{
		wordToDisplay[i] = '_';
	}
	guessLetter(wordToGuess[0]);
	guessLetter(wordToGuess[len - 1]);
	board.setPhase(0);
}

Game::Game(const size_t& boardPhase, const size_t& turns, const String& word, const String& display, const String& guessed, const String& alphabet):
	turnsPassed(turns), wordToGuess(word), wordToDisplay(display), guessedLetters(guessed), alphabet(alphabet), gameState(Ongoing)
{
	board.setPhase(boardPhase);
}


void Game::start()
{
	system("CLS");
	std::cout << "The word to be guessed: " << wordToDisplay << std::endl;
	board.print();
	std::cout << alphabet << std::endl << std::endl;
	std::cout << "Guess a letter ------> ";
}

void Game::guessLetter(char letter)
{
	if (letter < 97)
		letter += 32;

	if (!(letter >= 97 && letter <= 122))
		throw std::exception("Error! Invalid symbol!\nGuess a letter ---> ");

	else if (guessedLetters.contains(letter) != -1)
		throw std::exception("Letter already guessed!\nGuess a letter ---> ");

	guessedLetters += letter;
	size_t alphabetIndex = (letter - 97) * 2;
	alphabet[alphabetIndex] = ' ';

	int letterIndex = wordToGuess.contains(letter);
	if(letterIndex<0)
		board.advancePhase();
	else
	{
		size_t searchEnd = wordToGuess.getSize() - 2;
		for (size_t i = 1; i < searchEnd; i++)
		{
			if (wordToGuess[i] == letter)
				wordToDisplay[i] = letter;
		}
	}
}

void Game::makeTurn()
{
	char letter;
	std::cin >> letter;

	if (letter == '#')
	{
		gameState = OnHold;
		return;
	}

	try
	{
		guessLetter(letter);
	}
	catch (std::exception e)
	{
		throw e;
	}

	turnsPassed++;
	system("CLS");
	std::cout << "The word to be guessed: " << wordToDisplay << std::endl;
	board.print();
	std::cout << alphabet << std::endl << std::endl;

	if (wordToGuess == wordToDisplay)
		gameState = Win;

	else if (board.getPhase() == 9)
		gameState = Loss;

	else
		std::cout << "Guess a letter ------> ";
}

void Game::saveToFile(const String& user)
{
	String fileName = generateFileName(wordToGuess, user);
	String tempFileName = generateTempFile(wordToGuess, user);

	std::ofstream file(tempFileName.getData());
	file << board.getPhase() << ' ' << turnsPassed << ' ' << wordToGuess << ' ';
	file << wordToDisplay << ' ' << guessedLetters << ' ' << alphabet << std::endl;
	file.close();

	try
	{
		secureGameFile(fileName.getData());
	}
	catch (std::exception e)
	{
		throw e;
	}
	int state = remove(fileName.getData());
	if (state != 0)
		throw std::exception("Error! Could not delete old database file!");

	state = rename(tempFileName.getData(), fileName.getData());
	if (state != 0)
		throw std::exception("Error! Could not rename temp file");

	std::cout << "Game successfully saved!";

}

void Game::print()
{
	std::cout << board.getPhase() << ' ' << turnsPassed << ' ' << wordToGuess << ' ';
	std::cout << wordToDisplay << ' ' << guessedLetters << ' ' << alphabet << std::endl;
}


GameState Game::getState() const
{
	return gameState;
}

const String Game::getWordToGuess() const
{
	return wordToGuess;
}

void Game::setState(GameState state)
{
	gameState = state;
}