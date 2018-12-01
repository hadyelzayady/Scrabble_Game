#pragma once
#include "Square.h"
#include "Rack.h"
#include "ScoreManager.h"
#include "move.h"

/*
=> removeMoveTiles  : maynf3sh t3'er fe el rack 


*/


class EndSimulation
{
	ScoreManager *scoreManager;

public:
	//var for test only
	int i = 0;
	vector<Move>mymoves,opmoves;
	vector<Move> getplays();
	//
	Rack opponetRack;
	Rack myRack;
	Board board;
	/*
	pair<int,Move> minimax(Board board, int score, int alpha, int beta, bool maximizingPlayer);
	pair<int, Move> start();
	EndSimulation(const Board&board, ScoreManager *scoreManager, Rack opponentRack, Rack myRack);
	//test construcotr
	EndSimulation(const Board&board,ScoreManager *scoreManager, Rack opponentRack, Rack myRack,vector<Move>opmoves,vector<Move>mymoves);
	~EndSimulation();
	*/
	};   
