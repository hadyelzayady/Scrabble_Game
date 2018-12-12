#include "MidGameManager.h"



MidGameManager::MidGameManager(TileLookUp * Tp, Gaddag * GD)
{
	this->Heu = new Heuristics();
	this->MG = GD;
	this->TP = Tp;
}


MidGameManager::~MidGameManager()
{
}

int MidGameManager::getBestMove(const vector<Move> & movesList, Rack* Rack, Board * b)
{

	int size = movesList.size();
	cout << "Move Count: " << size << endl;
	int bestMoveIndex = -1;
	long double BestScore =LONG_MIN ;
	//long double EstimatedScore = 0;
	long double moveScore;
	long double heuristicScore;
	bool firstTurn = b->getBoardLetters().length() == 0;
	for (int i = 0; i < size; i++) {
		
		// Move Score
		moveScore = ScoreManager::calculateScore(movesList[i], b, this->TP);
		//cout << "Raw Score: " << moveScore << endl;

		// Heuristic Score
		heuristicScore = this->Heu->midGame(firstTurn, movesList[i], Rack->getLeave(movesList[i]), Rack->getUniqueLeave(movesList[i]));
		//cout << "Heuristic Score: " << heuristicScore << endl;

		// Total Score
		moveScore += heuristicScore;
		//cout << "Total Score: " << moveScore << endl;

		if (moveScore > BestScore) {
			BestScore = moveScore;
			bestMoveIndex = i;
		}
	}
	//cout << "Highest Score Move: " << BestScore << endl;
	return bestMoveIndex;
}