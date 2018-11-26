#include "ScoreManager.h"

double ScoreManager::computeMoveScore(Move M, Board *B)
{
	double resultantScore = 0;

	// counters for checking if this play passed over a word multiplier and how many times it passed
	// having these booleans calculated in the following loop will reduce computations since it won't need another loop
	int W2 = 0, W3 = 0;

	for (int i = 0; i < M.getPlaysPointer().size(); i++)
	{

		if (B->m_board[M.getPlaysPointer()[i].get_Coordinates().first][M.getPlaysPointer()[i].get_Coordinates().second].bonusType == WordBonusX2)
		{
			W3++;
		}

		if (B->m_board[M.getPlaysPointer()[i].get_Coordinates().first][M.getPlaysPointer()[i].get_Coordinates().second].bonusType == LetterBonusX2)
		{
			resultantScore += tileLookUp->getScore(M.getPlaysPointer()[i].get_Letter()) * 2;
		}
		else if (B->m_board[M.getPlaysPointer()[i].get_Coordinates().first][M.getPlaysPointer()[i].get_Coordinates().second].bonusType == LetterBonusX3)
		{
			resultantScore += tileLookUp->getScore(M.getPlaysPointer()[i].get_Letter()) * 3;
		}
		else
		{
			resultantScore += tileLookUp->getScore(M.getPlaysPointer()[i].get_Letter());
		}
	}

	resultantScore *= pow(2, W2);
	resultantScore *= pow(3, W3);
	return resultantScore;
}

ScoreManager::ScoreManager(Board *boardManager, TileLookUp *tileLookUp)
{
	this->boardManager = boardManager;
	this->tileLookUp = tileLookUp;
}

ScoreManager::~ScoreManager()
{
}
