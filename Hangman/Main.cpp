#include<iostream>
#include"GameSession.h"

int main()
{
	GameSession g;
	g.loadSavedGame("vesko01_947.hangman");
	try
	{
		g.createNewGame("testche");
	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}
	g.enterGameMenu("vesko01");
}