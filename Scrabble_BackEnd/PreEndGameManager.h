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
	Move * GoodEndGame();

};
inline double  Fishing(Move move, Board B, vector<char>RackLeave,Gaddag* MG,TileLookUp* Tup)
{
	Board newBoard = Board::commitMoveSim(move, B);

	vector<Move> moveList = MG->findWords(RackLeave, newBoard);
	double maxScorePerMove = 0.0f;
	int sizeMoveList = moveList.size();
	sizeMoveList = (sizeMoveList > 100)?  100:sizeMoveList;
	for (int i = 0; i < sizeMoveList; i++) {   //eb2a zabtha le el Size !!!
		double score = ScoreManager::calculateScore(moveList[i], newBoard, Tup);
		maxScorePerMove = (maxScorePerMove < score) ? score : maxScorePerMove;

	}
	return 0; maxScorePerMove;
}

