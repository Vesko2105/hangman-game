#pragma once
#include<iostream>
#include<fstream>
#include"Board.h"
#include"String.h"

enum GameState
{
	Ongoing, Win, Loss, OnHold
};

class Game
{
private:
	Board board;
	size_t turnsPassed;
	String wordToGuess;
	String wordToDisplay;
	String guessedLetters;
	String alphabet;
	GameState gameState;

public:
	Game(const String&);
	Game(const size_t&, const size_t&, const String&, const String&, const String&, const String&);

	void guessLetter(char);
	void start();
	void makeTurn();

	void saveToFile(const String&);
	void print();

	const String getWordToGuess() const;
	GameState getState() const;
	void setState(GameState state);
};

