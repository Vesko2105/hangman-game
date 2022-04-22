#pragma once
#include"Game.h"
#include"WordBank.h"
class GameSession
{
private:
	Game* currentGame;

public:
	GameSession();

	void createNewGame(const String& word);
	void loadSavedGame(const String& fileName);
	void saveGame(const String& user);
	void enterGameMenu(const String& user);
	void startGame(const String& user);
};

