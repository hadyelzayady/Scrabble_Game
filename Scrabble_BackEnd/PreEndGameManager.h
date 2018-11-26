#pragma once
#include "move.h"
#include "MonteCarlo.h"
#include "Board.h"
#include "Heuristics.h"
#include "ScoreManager.h"
class PreEndGameManager
{
	ScoreManager *scoreManager;
	Heuristics * Heu;
	vector<double> blockingCosts;
public:
	PreEndGameManager();
	~PreEndGameManager();
	Move GenerateMove();
	void  Blocking(Move  movesList[], Rack* Rack, Board b, ProbabilityManager *pm);
	Move * Fishing();
	Move * GoodEndGame();

};

