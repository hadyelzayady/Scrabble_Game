#include "ScoreManager.h"


int ScoreManager::computeMoveScore(int x[], int y[], char c[], int playCount) {
	int resultantScore = 0;
	
	// counters for checking if this play passed over a word multiplier and how many times it passed
	// having these booleans calculated in the following loop will reduce computations since it won't need another loop
	int W2 = 0, W3 = 0;

	for (int i = 0; i < playCount; i++) {
		if (boardManager->m_board[x[i]][y[i]].bonusType == WordBonusX2) {
			W2++;
		}
		else if (boardManager->m_board[x[i]][y[i]].bonusType == WordBonusX3) {
			W3++;
		}
		else if (boardManager->m_board[x[i]][y[i]].bonusType == LetterBonusX2) {
			resultantScore += tileLookUp->getScore(c[i]) * 2;
		}
		else if (boardManager->m_board[x[i]][y[i]].bonusType == LetterBonusX3) {
			resultantScore += tileLookUp->getScore(c[i]) * 3;
		}
		else {
			resultantScore += tileLookUp->getScore(c[i]);
		}
	}

	resultantScore *= (int)pow(2, W2);
	resultantScore *= (int) pow(3, W3);
	return resultantScore;
}


ScoreManager::ScoreManager(Board* boardManager, TileLookUp* tileLookUp)
{
	this->boardManager = boardManager;
	this->tileLookUp = tileLookUp;
}


ScoreManager::~ScoreManager()
{
}
