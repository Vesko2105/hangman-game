#pragma once
#include"String.h"
#include<iostream>
class Board
{
private:
	unsigned short phase;
	String phases[10] = {
							"\n \n \n \n \n \n                     ___________\n\n--------------------Letters Left--------------------",
							"\n                    | \n                    | \n                    | \n                    | \n                    | \n                    |___________\n\n--------------------Letters Left--------------------",
							"                     ___________\n                    | \n                    | \n                    | \n                    | \n                    | \n                    |___________\n\n--------------------Letters Left--------------------",
							"                     ___________\n                    |     |\n                    | \n                    | \n                    | \n                    | \n                    |___________\n\n--------------------Letters Left--------------------",
							"                     ___________\n                    |     |\n                    |     O\n                    | \n                    | \n                    | \n                    |___________\n\n--------------------Letters Left--------------------",
							"                     ___________\n                    |     |\n                    |     O\n                    |     |\n                    | \n                    | \n                    |___________\n\n--------------------Letters Left--------------------",
							"                     ___________\n                    |     |\n                    |     O\n                    |    /|\n                    | \n                    | \n                    |___________\n\n--------------------Letters Left--------------------",
							"                     ___________\n                    |     |\n                    |     O\n                    |    /|\\\n                    | \n                    | \n                    |___________\n\n--------------------Letters Left--------------------",
							"                     ___________\n                    |     |\n                    |     O\n                    |    /|\\\n                    |    /\n                    | \n                    |___________\n\n--------------------Letters Left--------------------",
							"                     ___________\n                    |     |\n                    |     O\n                    |    /|\\\n                    |    / \\ \n                    |\n                    |___________\n\n--------------------Letters Left--------------------",
						};
public:
	Board();

	size_t getPhase();
	void setPhase(const unsigned short&);

	void print();
	void advancePhase();
	void reset();
};

