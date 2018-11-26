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

double Heuristics::getHeuristics(int turn, vector<char> estimatedRack, Rack  current, Move  move, BagOfLetters bag, vector < pair<int, int>>  Qpos, vector < pair<int, int> > Zpos)
// leave is the remaining rack after the move is played
{																										//bag is left private in the class BagOfLetters
																									//turn to decide the openinng move of the game
	vector<char> leave;
	vector<Play> plays = move.getPlaysPointer();
	char * c = current.getRackTiles();
	for (int i = 0; i < current.getSize(); i++)
	{
		leave.push_back(c[i])
	}
	for (int i = 0; i < plays.size(); i++)
	{
		for (int k = 0; k < leave.size(); k++)
		{
			if (leave[k] == plays[i].get_Letter())
				leave.erase(leave.begin() + k);
		}

	}

	if (bag.getSize() == 0) return endGame(estimatedRack, move, Qpos, Zpos);
	else if (bag.getSize() < 10 && bag.getSize() > 0) return preEnd(move, leave);
	else return midGame(turn, move, leave);

}
double Heuristics::endGame(vector<char> estimatedRack, Move move, vector<pair<int, int>>  Qpos, vector<pair<int, int>>  Zpos)
{
	double cost = 0.0;
	vector<Play> plays = move.getPlaysPointer();
	bool hasQ = false;
	bool hasZ = false;
	TileLookUp t;

	for (int i = 0; i < estimatedRack.size(); i++)
	{
		if (estimatedRack[i] == 'Q')hasQ = true;
		if (estimatedRack[i] == 'Z')hasZ = true;
	}
	int priority = 1;
	for (int i = 0; i < plays.size(); i++)
	{
		if (hasQ)
		{
			for (int k = 0; k < Qpos.size(); k++)
			{
				if (plays[i].get_Coordinates() == Qpos[k])
				{
					priority++;
				}

			}

		}
		if (hasZ)
		{
			for (int k = 0; k < Zpos.size(); k++)
			{
				if (plays[i].get_Coordinates() == Zpos[k])
				{
					priority++;
				}

			}
		}

		cost -= t.getScore(plays[i].get_Letter());

	}

	cost = cost * priority;
	cost = cost * (1 - (plays.size() / 7)); //short word move has less cost than long word move

	return cost;
}
double Heuristics::preEnd(Move move, vector<char>  leave)
{

	double cost = 0.0;
	int vowels = 0;
	int cons = 0;

	for (int i = 0; i < leave.size(); i++)
	{
		if (leave[i] != BLANK_TILE)
		{
			if (leave[i] == 'A' || leave[i] == 'E' || leave[i] == 'I' || leave[i] == 'O' || leave[i] == 'U')
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
double Heuristics::midGame(int turn, Move  move, vector<char> leave)
{
	double cost = 0.0;
	vector<Play> plays = move.getPlaysPointer();
	if (turn == 0)
	{
		if (plays.size() == 7)
		{
			cost += 50;
		}
	}
	int vowels = 0;
	int cons = 0;
	for (int i = 0; i < leave.size(); i++)
	{
		if (leave[i] != BLANK_TILE)
		{
			if (leave[i] == 'A' || leave[i] == 'E' || leave[i] == 'I' || leave[i] == 'O' || leave[i] == 'U')
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


