#include "Heuristics.h"



const float vcvalues[8][8] =
{
	{  0.0,   0.0,  -1.0,  -2.5,  -5.0,  -8.5, -13.5, -18.5},
	{ -1.0,   0.0,   0.5,   0.0,  -1.5,  -5.0, -10.0,   0.0},
	{ -3.5,  -1.0,   0.5,   1.5,  -1.5,  -3.0,   0.0,   0.0},
	{ -7.0,  -3.5,  -0.5,   2.5,   0.0,   0.0,   0.0,   0.0},
	{-10.0,  -6.5,  -3.0,   0.0,   0.0,   0.0,   0.0,   0.0},
	{-13.5, -11.5,  -8.0,   0.0,   0.0,   0.0,   0.0,   0.0},
	{-18.5, -16.5,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0},
	{-23.5,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0},
};


Heuristics::Heuristics()
{

}



int Heuristics::getHeuristics(int turn,Rack * estimatedRack,Rack * leave, Move  *move, BagOfLetters *bag)// leave is the remaining rack after the move is played
{																										//bag is left private in the class BagOfLetters
																										//turn to decide the openinng move of the game
	if (bag->getSize() == 0) return -1;//endGame(estimatedRack,move,leave);
	else if (bag->getSize() < 10 && bag->getSize() >0) return preEnd(* move, leave);
	else return midGame(turn,estimatedRack, move, leave);

}


int Heuristics::preEnd( Move move, Rack * leave)
{

	double cost = 0.0;
	int vowels = 0;
	int cons = 0;
	char *c = leave->getRackTiles();
	for (int i = 0; i < leave->getSize(); i++)
	{
		if (c[i] != BLANK_TILE)
		{
			if (c[i] == 'A' || c[i] == 'E' || c[i] == 'I' || c[i] == 'O' || c [i] == 'U')
				vowels++;
			else
				cons++;
		}
	}
	cost += vcvalues[vowels][cons];


	TileLookUp t;
	int priority = 1;
	if (move.getPlaysPointer().size() == 7)
	{
		priority = 2;
	}
	for (int i = 0; i < move.getPlaysPointer().size(); i++)// here the move should already have a score generating function to take into consideration
											//the tile location for special bonus on the board
	{
		if (move.getPlaysPointer()[i].get_Letter() == 'Q' || move.getPlaysPointer()[i].get_Letter() == 'U' || move.getPlaysPointer()[i].get_Letter() == 'Z' || move.getPlaysPointer()[i].get_Letter() == 'X')
		{
			priority++;
		}

		cost -= t.getScore(move.getPlaysPointer()[i].get_Letter());

	}
	cost = cost * priority;
	return cost;
}

int Heuristics::midGame(int turn,Rack * estimatedRack, Move * move, Rack * leave)
{
	double cost=0.0;
	vector<Play> plays = move->getPlaysPointer();
	if (turn == 0)
	{
		if (plays.size() == 7)
		{
			cost += 50;
		}
	}
	int vowels = 0;
	int cons = 0;
	char *c = leave->getRackTiles();
	for (int i=0;i<leave->getSize();i++)
	{
		if (c[i] != BLANK_TILE)
		{
			if (c[i] == 'A' || c[i] == 'E' || c[i] == 'I' || c[i] == 'O' || c[i]== 'U')
				vowels++;
			else
				cons++;
		}
	}
	cost += vcvalues[vowels][cons];
	TileLookUp t;
	for (int i = 0; i < plays.size(); i++)// here the move should already have a score generating function to take into consideration
											//the tile location for special bonus on the board
	{
		cost -= t.getScore(plays[i].get_Letter());
		
	}

	return cost;
}

Heuristics::~Heuristics()
{
}


