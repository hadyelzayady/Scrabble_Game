#include "ScoreManager.h"

double ScoreManager::calculateScore(const Move & m, Board * board,  TileLookUp * tileLookUp) {
	double score = 0;
	int wordMult = 1;
	int wordScore = 0;
	int Playi, playlen;
	for (Playi = 0, playlen = m.Plays.size(); Playi < playlen ;Playi++ ) {
		if (!board->isEmptySquare(m.Plays[Playi].coordinates.second, m.Plays[Playi].coordinates.first))	//if square already has a tile skip it, will be counted by its anchor square in case lw haraga3 move feha el 7agat kolha msh el plays bas 
			continue;
		else if (board->isAnchor(m.Plays[Playi].coordinates.second, m.Plays[Playi].coordinates.first)) {
			int tempScore = 0;			//accumulated score of other words this play has made
			bool otherWords = false;
			int l = m.Plays[Playi].coordinates.first - 1;
			int r = m.Plays[Playi].coordinates.first + 1;
			int u = m.Plays[Playi].coordinates.second - 1;
			int d = m.Plays[Playi].coordinates.second + 1;
			while (!board->isEmptySquare(m.Plays[Playi].coordinates.second, l)) {	//while tile to left
				if (board->m_board[m.Plays[Playi].coordinates.second][l].blank == false) {
					tempScore += tileLookUp->getScore(board->m_board[m.Plays[Playi].coordinates.second][l].letter);
				}
				l--;
				otherWords = true;
			}
			while (!board->isEmptySquare(m.Plays[Playi].coordinates.second, r)) {	//while tile to right
				if (board->m_board[m.Plays[Playi].coordinates.second][r].blank == false) {
					tempScore += tileLookUp->getScore(board->m_board[m.Plays[Playi].coordinates.second][r].letter);
				}
				r++;
				otherWords = true;
			}
			while (!board->isEmptySquare(d, m.Plays[Playi].coordinates.first)) {	//while tile to down
				if (board->m_board[d][m.Plays[Playi].coordinates.first].blank == false) {
					tempScore += tileLookUp->getScore(board->m_board[d][m.Plays[Playi].coordinates.first].letter);
				}
				d++;
				otherWords = true;
			}
			while (!board->isEmptySquare(u, m.Plays[Playi].coordinates.first)) {	//while tile to up
				if (board->m_board[u][m.Plays[Playi].coordinates.first].blank == false) {
					tempScore += tileLookUp->getScore(board->m_board[u][m.Plays[Playi].coordinates.first].letter);
				}
				u--;
				otherWords = true;
			}
			if (m.Plays[Playi].Blank == false) {
				tempScore += tileLookUp->getScore(m.Plays[Playi].Letter) *
					board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getLetterMultiplier();
			}
			if (otherWords) {
				tempScore *= board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getWordMultiplier();
				score += tempScore;
			}

			wordMult *= board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getWordMultiplier();
			if (m.Plays[Playi].Blank == false) {
				wordScore += tileLookUp->getScore(m.Plays[Playi].Letter) *
					board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getLetterMultiplier();    // el word ely ana kawenta fe el move msh ba2y el kalemat 
			}
		}
		else {
			wordMult *= board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getWordMultiplier();
			if (m.Plays[Playi].Blank == false) {
				wordScore += tileLookUp->getScore(m.Plays[Playi].Letter) *
					board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getLetterMultiplier();
			}
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
