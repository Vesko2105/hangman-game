#pragma once
#include<vector>
#include<fstream>
#include <stdlib.h>
#include <time.h>  
#include"String.h"
class WordBank
{
private:
	std::vector<String> words;

	bool secureFile();
	void loadWordsFromFile();
public:
	WordBank();

	void printWords();
	void addNewWord(String newWord);
	String getRandomWord();
};

