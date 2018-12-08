#pragma once
#include "Square.h"
#include "Rack.h"
#include "ScoreManager.h"
#include "move.h"
#include "BStarNode.h"
#include "Gaddag.h"
#include "Heuristics.h"
class EndSimulation
{
	ScoreManager *scoreManager;

  public:
	//var for test only
	int i = 0;
	Gaddag * MG;
	Heuristics* hr;
	vector<Move>moves;// moves from parent to node
	vector<Move> mymoves, opmoves;
	vector<Move> getplays();
	unordered_map<int, vector<BStarNode>> cache;

	//
	TileLookUp *tileLookup;
	Rack opponetRack;
	Rack myRack;
	Board board;
	vector<BStarNode>* getChildren(const BStarNode& node, Rack& myrack, Rack&oprac, bool ismax, vector<BStarNode *>& bestFirstAndSecond);
	pair<int, Move> minimax(Board board, int score, int alpha, int beta, bool maximizingPlayer);
	BStarNode BStar(BStarNode &node, int depth, bool maximizingPlayer,Rack myrack,Rack oprack);
	Move start();
	EndSimulation(const Board &board, TileLookUp*tl, Rack opponentRack, Rack myRack, Gaddag* GD, Heuristics* hr);
	//test construcotr
	~EndSimulation();
};
