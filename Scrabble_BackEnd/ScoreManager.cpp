#include "ScoreManager.h"






double ScoreManager::calculateScore(const Move & m,const Board &  board,  TileLookUp * tileLookUp) {
	double score = 0;
	int wordMult = 1;
	int wordScore = 0;
	for (Play p : m.Plays) {
		if (!board.isEmptySquare(p.coordinates.second, p.coordinates.first))	//if square already has a tile skip it, will be counted by its anchor square in case lw haraga3 move feha el 7agat kolha msh el plays bas 
			continue;
		else if (!board.isAnchor(p.coordinates.second, p.coordinates.first)) {
			int tempScore = 0;			//accumulated score of other words this play has made
			bool otherWords = false;
			int l = p.coordinates.first - 1;
			int r = p.coordinates.first + 1;
			int u = p.coordinates.second - 1;
			int d = p.coordinates.second + 1;
			while (!board.isEmptySquare(p.coordinates.second, l)) {	//while tile to left
				tempScore += tileLookUp->getScore(board.getLetter(p.coordinates.second, l));
				l--;
				otherWords = true;
			}
			while (!board.isEmptySquare(p.coordinates.second, r)) {	//while tile to right
				tempScore += tileLookUp->getScore(board.getLetter(p.coordinates.second, r));
				r++;
				otherWords = true;
			}
			while (!board.isEmptySquare(d, p.coordinates.first)) {	//while tile to down
				tempScore += tileLookUp->getScore(board.getLetter(d, p.coordinates.first));
				d++;
				otherWords = true;
			}
			while (!board.isEmptySquare(u, p.coordinates.first)) {	//while tile to up
				tempScore += tileLookUp->getScore(board.getLetter(u, p.coordinates.first));
				u--;
				otherWords = true;
			}
			tempScore += tileLookUp->getScore(board.getLetter(p.coordinates.second, p.coordinates.first)) *
				board.m_board[p.coordinates.second][p.coordinates.first].getLetterMultiplier();
			/// assume get Letter multiplier is a function in square that checks bonus type and returns the letter multiplyer if there is any or returns 1 
			if (otherWords) {
				tempScore *= board.m_board[p.coordinates.second][p.coordinates.first].getWordMultiplier();
				score += tempScore;
			}

			wordMult *= board.m_board[p.coordinates.second][p.coordinates.first].getWordMultiplier();
			wordScore += tileLookUp->getScore(board.getLetter(p.coordinates.second, p.coordinates.first)) *
				board.m_board[p.coordinates.second][p.coordinates.first].getLetterMultiplier();    // el word ely ana kawenta fe el move msh ba2y el kalemat 
		}
		else {
			wordMult *= board.m_board[p.coordinates.second][p.coordinates.first].getWordMultiplier();
			wordScore += tileLookUp->getScore(board.getLetter(p.coordinates.second, p.coordinates.first)) *
				board.m_board[p.coordinates.second][p.coordinates.first].getLetterMultiplier();
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
