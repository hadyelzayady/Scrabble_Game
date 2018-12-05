#pragma once
#include "move.h"
#include "MonteCarlo.h"
#include "Board.h"
#include "Heuristics.h"
#include "ScoreManager.h"
#include "Gaddag.h"
#include <math.h>
class PreEndGameManager
{
	ScoreManager *scoreManager;
	Heuristics * Heu;
	Gaddag * MG;
	TileLookUp * TP;

public:

	PreEndGameManager(TileLookUp * Tp, Gaddag * GD);
	~PreEndGameManager();
	Move GenerateMove();
	Move  Blocking(vector<Move> movesList, Rack* Rack, Board b, ProbabilityManager *pm);
	double Fishing(const Move & move, const Board & B, const vector<char>& RackLeave, Gaddag * MG, TileLookUp * Tup);
	Move * GoodEndGame();

};
