#pragma once
#include "Rack.h"
#include "move.h"
#include "BagOfLetters.h"
#include "TileLookUp.h"




class Heuristics
{

public:
	Heuristics();
	double getHeuristics(int turn, vector<char> estimatedRack, Rack  current, Move  move, BagOfLetters bag, vector < pair<int, int>>Qpos, vector < pair<int, int>> Zpos);
	double endGame(vector<char> estimatedRack, Move move, vector<pair<int, int>>  Qpos, vector<pair<int, int>>  Zpos);
	double preEnd(Move move, vector<char>  leave);
	double midGame(int turn, Move  move, vector<char> leave);


	~Heuristics();
};




