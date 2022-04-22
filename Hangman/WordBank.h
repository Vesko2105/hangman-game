#pragma once
#include<vector>
#include"String.h"
class WordBank
{
private:
	static std::vector<String> words;

	void loadWordsFromFile();
	bool validateWord();
public:
	static void addNewWord();
};

