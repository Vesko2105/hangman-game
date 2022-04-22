#include "Board.h"

Board::Board():phase(0)
{
	;
}

size_t Board::getPhase()
{
	return phase;
}

void Board::setPhase(const unsigned short& x)
{
	phase = x;
}

void Board::print()
{
	std::cout << phases[phase] << std::endl;
}

void Board::advancePhase()
{
	if (phase > 8)
		throw "Last phase reached!";
	phase += 1;
}

void Board::reset()
{
	phase = 0;
}
