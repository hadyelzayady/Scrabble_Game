#pragma once
#include "Square.h"
#include "Rack.h"
#include "ScoreManager.h"
#include "move.h"
#include "BStarNode.h"
#include "Gaddag.h"
#include "Heuristics.h"
#include "TileLookUp.h"
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
	unordered_map<int, vector<BStarNode>> cache;

	//
	TileLookUp *tileLookup;
	Rack opponetRack;
	Rack myRack;
	Board board;
	void getOpRack();
	vector<BStarNode>* getChildren(const BStarNode& node, Rack& myrack, Rack&oprac, bool ismax, vector<BStarNode *>& bestFirstAndSecond);
	BStarNode BStar(BStarNode &node, int depth, bool maximizingPlayer,Rack myrack,Rack oprack);
	Move start();
	EndSimulation(const Board &board, TileLookUp*tl, Rack opponentRack, Rack myRack, Gaddag* GD, Heuristics* hr);
	//test construcotr
	~EndSimulation();
};
