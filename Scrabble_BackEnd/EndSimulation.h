#pragma once
#include "Square.h"
#include "Rack.h"
#include "ScoreManager.h"
#include "move.h"
#include "BStarNode.h"
#include "Gaddag.h"
class EndSimulation
{
	ScoreManager *scoreManager;

  public:
	//var for test only
	int i = 0;
	Gaddag * MG;
	vector<Move> mymoves, opmoves;
	vector<Move> getplays();
	//
	TileLookUp *tileLookup;
	Rack opponetRack;
	Rack myRack;
	Board board;
	vector<BStarNode>* getChildren(const BStarNode& node,Rack&rack, bool ismax);
	pair<int, Move> minimax(Board board, int score, int alpha, int beta, bool maximizingPlayer);
	BStarNode BStar(BStarNode &node, int depth, bool maximizingPlayer,Rack rack);
	pair<int, Move> start();
	EndSimulation(const Board &board, TileLookUp*tl, Rack opponentRack, Rack myRack, Gaddag* GD);
	//test construcotr
	~EndSimulation();
};
