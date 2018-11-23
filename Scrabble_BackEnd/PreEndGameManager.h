#pragma once
#include "move.h"
#include "MonteCarlo.h"
#include "Board.h"
class PreEndGameManager
{
	vector<double> costs;
public:
	PreEndGameManager();
	~PreEndGameManager();
	Move GenerateMove();
	Move * Blocking(Move  movesList[], Rack Rack, Board board, ProbabilityManager *pm);
	Move * Fishing();
	Move * GoodEndGame();

};

