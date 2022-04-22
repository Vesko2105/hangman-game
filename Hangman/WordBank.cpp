#include "WordBank.h"

const size_t BUFF_SIZE = 64;

bool WordBank::secureFile()
{
	std::ofstream file;
	file.open("word-bank.hangman", std::ios::app);
	if (!file.is_open())
	{
		file.close();
		return false;
	}
	file.close();
	return true;
}

void WordBank::loadWordsFromFile()
{
	secureFile();
	std::ifstream wordsFile;
	wordsFile.open("word-bank.hangman");
	if (!wordsFile.is_open())
	{
		throw std::exception("Error! Could not access wordBank file!");
	}
	while (!wordsFile.eof())
	{
		String word;
		word.getline(wordsFile, BUFF_SIZE);
		if(word != "\0")
		words.push_back(word);
	}
	wordsFile.close();
}

String WordBank::getRandomWord()
{
	srand(time(NULL));
	size_t random = rand() % words.size();
	return words[random];
}

WordBank::WordBank()
{
	loadWordsFromFile();
}

void WordBank::printWords()
{
	for (size_t i = 0; i < words.size(); i++)
	{
		std::cout << words[i] << std::endl;
	}
}

void WordBank::addNewWord(String newWord)
{
	std::ofstream wordsFile;
	wordsFile.open("word-bank.hangman", std::ios::app);
	if (!wordsFile.is_open())
	{
		throw std::exception("Error! Could not access wordBank file!");
	}
	wordsFile << newWord << std::endl;
	wordsFile.close();
	words.push_back(newWord);
}
