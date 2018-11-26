#pragma once
#include "Rack.h"
#include "move.h"
#include "BagOfLetters.h"
#include "TileLookUp.h"



struct GamePosition
{
int player1score;
int player2score;
};

class Heuristics
{



public:
	Heuristics( );
	int getHeuristics(int turn, Rack * estimatedRack, Rack * leave, Move  *move, BagOfLetters *bag);
	int preEnd( Move move, Rack * leave);
	int midGame(int turn, Rack * estimatedRack, Move * move, Rack * leave);


	~Heuristics();
};




