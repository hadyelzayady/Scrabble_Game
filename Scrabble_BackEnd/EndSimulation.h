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
	static long id;
	const int QVAL = 50;
	const int ZVAL = 1.5;
	const int JVAL = 1.2;


  public:
	//var for test only
	Gaddag * MG;
	Heuristics* hr;
	void estimateOPRack();
	void updateOPRack( Move&move);


	unordered_map<int, vector<BStarNode>> cache;
	TileLookUp *tileLookup;
	Rack opponetRack;
	Rack myRack;
	Board* board;
	void getOpRack();
	vector<BStarNode>* getChildren(const BStarNode& node, Rack& myrack, Rack&oprac, bool ismax, vector<BStarNode *>& bestFirstAndSecond);
	BStarNode BStar(BStarNode &node, int depth, bool maximizingPlayer,Rack myrack,Rack oprack);
	Move start();
	EndSimulation(Board *board, TileLookUp*tl, Rack opponentRack, Rack myRack, Gaddag* GD, Heuristics* hr);
	//test construcotr
	~EndSimulation();
};
