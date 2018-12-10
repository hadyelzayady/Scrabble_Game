#include "ScoreManager.h"

double ScoreManager::calculateScore(const Move & m, Board * board,  TileLookUp * tileLookUp) {
	double score = 0;
	int wordMult = 1;
	int wordScore = 0;
	for (int Playi = 0; Playi < m.Plays.size();Playi++ ) {
		if (!board->isEmptySquare(m.Plays[Playi].coordinates.second, m.Plays[Playi].coordinates.first))	//if square already has a tile skip it, will be counted by its anchor square in case lw haraga3 move feha el 7agat kolha msh el plays bas 
			continue;
		else if (!board->isAnchor(m.Plays[Playi].coordinates.second, m.Plays[Playi].coordinates.first)) {
			int tempScore = 0;			//accumulated score of other words this play has made
			bool otherWords = false;
			int l = m.Plays[Playi].coordinates.first - 1;
			int r = m.Plays[Playi].coordinates.first + 1;
			int u = m.Plays[Playi].coordinates.second - 1;
			int d = m.Plays[Playi].coordinates.second + 1;
			while (!board->isEmptySquare(m.Plays[Playi].coordinates.second, l)) {	//while tile to left
				tempScore += tileLookUp->getScore(m.Plays[Playi].Letter);
				l--;
				otherWords = true;
			}
			while (!board->isEmptySquare(m.Plays[Playi].coordinates.second, r)) {	//while tile to right
				tempScore += tileLookUp->getScore(m.Plays[Playi].Letter);
				r++;
				otherWords = true;
			}
			while (!board->isEmptySquare(d, m.Plays[Playi].coordinates.first)) {	//while tile to down
				tempScore += tileLookUp->getScore(m.Plays[Playi].Letter);
				d++;
				otherWords = true;
			}
			while (!board->isEmptySquare(u, m.Plays[Playi].coordinates.first)) {	//while tile to up
				tempScore += tileLookUp->getScore(m.Plays[Playi].Letter);
				u--;
				otherWords = true;
			}
			tempScore += tileLookUp->getScore(m.Plays[Playi].Letter) *
				board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getLetterMultiplier();
			/// assume get Letter multiplier is a function in square that checks bonus type and returns the letter multiplyer if there is any or returns 1 
			if (otherWords) {
				tempScore *= board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getWordMultiplier();
				score += tempScore;
			}

			wordMult *= board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getWordMultiplier();
			wordScore += tileLookUp->getScore(m.Plays[Playi].Letter) *
				board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getLetterMultiplier();    // el word ely ana kawenta fe el move msh ba2y el kalemat 
		}
		else {
			wordMult *= board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getWordMultiplier();
			wordScore += tileLookUp->getScore(m.Plays[Playi].Letter) *
				board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getLetterMultiplier();
		}
	}
	if (m.isBingo)
		score += 50;
	return (score += wordScore * wordMult);
}

ScoreManager::ScoreManager(Board* boardManager, TileLookUp* tileLookUp)
{
	this->boardManager = boardManager;
	this->tileLookUp = tileLookUp;
}

ScoreManager::~ScoreManager()
{
}
