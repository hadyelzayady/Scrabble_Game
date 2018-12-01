#pragma once
#include "move.h"
#include "MonteCarlo.h"
#include "Board.h"
#include "Heuristics.h"
#include "ScoreManager.h"
#include "Gaddag.h"
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
	Move  Blocking(Move  movesList[], Rack* Rack, Board b, ProbabilityManager *pm);
	Move * GoodEndGame();

};
inline double  Fishing(Move move, Board B, vector<char>RackLeave,Gaddag* MG,TileLookUp* Tup)
{
	Board newBoard = Board::commitMoveSim(move, B);

	vector<Move> moveList = MG->findWords(RackLeave, newBoard);
	double maxScorePerMove = 0.0f;
	int sizeMoveList = moveList.size();
	for (int i = 0; i < sizeMoveList; i++) {
		double score = ScoreManager::calculateScore(moveList[i], newBoard, Tup);
		maxScorePerMove = (maxScorePerMove < score) ? score : maxScorePerMove;

	}
	return 0; maxScorePerMove;
}

