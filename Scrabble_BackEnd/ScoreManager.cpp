#include "ScoreManager.h"

//double ScoreManager::calculateScore(const Move & m, Board * board,  TileLookUp * tileLookUp) {
//	double score = 0;
//	int wordMult = 1;
//	int wordScore = 0;
//	int Playi, playlen;
//	for (Playi = 0, playlen = m.Plays.size(); Playi < playlen ;Playi++ ) {
//		if (!board->isEmptySquare(m.Plays[Playi].coordinates.second, m.Plays[Playi].coordinates.first))	//if square already has a tile skip it, will be counted by its anchor square in case lw haraga3 move feha el 7agat kolha msh el plays bas 
//			continue;
//		else if (board->isAnchor(m.Plays[Playi].coordinates.second, m.Plays[Playi].coordinates.first)) {
//			int tempScore = 0;			//accumulated score of other words this play has made
//			bool otherWords = false;
//			int l = m.Plays[Playi].coordinates.first - 1;
//			int r = m.Plays[Playi].coordinates.first + 1;
//			int u = m.Plays[Playi].coordinates.second - 1;
//			int d = m.Plays[Playi].coordinates.second + 1;
//			while (!board->isEmptySquare(m.Plays[Playi].coordinates.second, l)) {	//while tile to left
//				if (board->m_board[m.Plays[Playi].coordinates.second][l].blank == false) {
//					tempScore += tileLookUp->getScore(board->m_board[m.Plays[Playi].coordinates.second][l].letter);
//				}
//				l--;
//				otherWords = true;
//			}
//			while (!board->isEmptySquare(m.Plays[Playi].coordinates.second, r)) {	//while tile to right
//				if (board->m_board[m.Plays[Playi].coordinates.second][r].blank == false) {
//					tempScore += tileLookUp->getScore(board->m_board[m.Plays[Playi].coordinates.second][r].letter);
//				}
//				r++;
//				otherWords = true;
//			}
//			while (!board->isEmptySquare(d, m.Plays[Playi].coordinates.first)) {	//while tile to down
//				if (board->m_board[d][m.Plays[Playi].coordinates.first].blank == false) {
//					tempScore += tileLookUp->getScore(board->m_board[d][m.Plays[Playi].coordinates.first].letter);
//				}
//				d++;
//				otherWords = true;
//			}
//			while (!board->isEmptySquare(u, m.Plays[Playi].coordinates.first)) {	//while tile to up
//				if (board->m_board[u][m.Plays[Playi].coordinates.first].blank == false) {
//					tempScore += tileLookUp->getScore(board->m_board[u][m.Plays[Playi].coordinates.first].letter);
//				}
//				u--;
//				otherWords = true;
//			}
//			if (m.Plays[Playi].Blank == false) {
//				tempScore += tileLookUp->getScore(m.Plays[Playi].Letter) *
//					board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getLetterMultiplier();
//			}
//			if (otherWords) {
//				tempScore *= board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getWordMultiplier();
//				score += tempScore;
//			}
//
//			wordMult *= board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getWordMultiplier();
//			if (m.Plays[Playi].Blank == false) {
//				wordScore += tileLookUp->getScore(m.Plays[Playi].Letter) *
//					board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getLetterMultiplier();    // el word ely ana kawenta fe el move msh ba2y el kalemat 
//			}
//		}
//		else {
//			wordMult *= board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getWordMultiplier();
//			if (m.Plays[Playi].Blank == false) {
//				wordScore += tileLookUp->getScore(m.Plays[Playi].Letter) *
//					board->m_board[m.Plays[Playi].coordinates.second][m.Plays[Playi].coordinates.first].getLetterMultiplier();
//			}
//		}
//	}
//	if (m.isBingo)
//		score += 50;
//	return (score += wordScore * wordMult);
//}

ScoreManager::ScoreManager(Board* boardManager, TileLookUp* tileLookUp)
{
	this->boardManager = boardManager;
	this->tileLookUp = tileLookUp;
}

double ScoreManager::calculateScore(Move & m, Board * board, TileLookUp * tileLookUp) {

	double score=0.0;
	if (board->checkMoveHorizontal(m)) {
	
		m.sortPlaysFirst(m.Plays);   // sort the plays according the x value
		int wordMult = 1;
		int horizontalTemp = 0; // score of horizontal word

		int i, ilen;
		for (i = 0, ilen = m.Plays.size(); i < ilen; ++i) {
			if (i == 0) {
				int l = m.Plays[i].coordinates.first - 1;
				while (!board->isEmptySquare(m.Plays[i].coordinates.second, l)) {
					if (board->m_board[m.Plays[i].coordinates.second][l].blank == false) {
						horizontalTemp += tileLookUp->getScore(board->m_board[m.Plays[i].coordinates.second][l].letter);
					}
					l--;
				}
			}

			int r = m.Plays[i].coordinates.first + 1;
			while (!board->isEmptySquare(m.Plays[i].coordinates.second, r)) {	//while tile to right
				if (board->m_board[m.Plays[i].coordinates.second][r].blank == false) {
					horizontalTemp += tileLookUp->getScore(board->m_board[m.Plays[i].coordinates.second][r].letter);
				}
				r++;
			}
			
			int verticalTemp=0;
			bool otherVerticalWords = false;
			int d = m.Plays[i].coordinates.second + 1;

			while (!board->isEmptySquare(d, m.Plays[i].coordinates.first)) {	//while tile to down
				if (board->m_board[d][m.Plays[i].coordinates.first].blank == false) {
					verticalTemp += tileLookUp->getScore(board->m_board[d][m.Plays[i].coordinates.first].letter);
				}
				d++;
				otherVerticalWords = true;
			}

			int u = m.Plays[i].coordinates.second - 1;

			while (!board->isEmptySquare(u, m.Plays[i].coordinates.first)) {	//while tile to up
				if (board->m_board[u][m.Plays[i].coordinates.first].blank == false) {
					verticalTemp += tileLookUp->getScore(board->m_board[u][m.Plays[i].coordinates.first].letter);
				}
				u--;
				otherVerticalWords = true;
			}
			if (m.Plays[i].Blank == false) {
				horizontalTemp += tileLookUp->getScore(m.Plays[i].Letter) *
					board->m_board[m.Plays[i].coordinates.second][m.Plays[i].coordinates.first].getLetterMultiplier();
			}
			if (otherVerticalWords) {
				if (m.Plays[i].Blank == false) {
					verticalTemp += tileLookUp->getScore(m.Plays[i].Letter) *
						board->m_board[m.Plays[i].coordinates.second][m.Plays[i].coordinates.first].getLetterMultiplier();
				}
				verticalTemp *= board->m_board[m.Plays[i].coordinates.second][m.Plays[i].coordinates.first].getWordMultiplier();
				score += verticalTemp;
			}
			wordMult *= board->m_board[m.Plays[i].coordinates.second][m.Plays[i].coordinates.first].getWordMultiplier();

		}

		if (m.isBingo)
			score += 50;
		score+= horizontalTemp * wordMult;
	}
	else {

		m.sortPlaysSecond(m.Plays);   // sort the plays according the x value
		int wordMult = 1;
		int verticalTemp = 0; // score of horizontal word
		//bool otherHorizontalWords = false;
		int i, ilen;
		for (i = 0, ilen = m.Plays.size(); i < ilen; ++i) {
			if (i == 0) {
				int u = m.Plays[i].coordinates.second - 1;
				while (!board->isEmptySquare(u, m.Plays[i].coordinates.first)) {	//while tile to up
					if (board->m_board[u][m.Plays[i].coordinates.first].blank == false) {
						verticalTemp += tileLookUp->getScore(board->m_board[u][m.Plays[i].coordinates.first].letter);
					}
					u--;
				}
			}

			int d = m.Plays[i].coordinates.second + 1;
			while (!board->isEmptySquare(d, m.Plays[i].coordinates.first)) {	//while tile to down
				if (board->m_board[d][m.Plays[i].coordinates.first].blank == false) {
					verticalTemp += tileLookUp->getScore(board->m_board[d][m.Plays[i].coordinates.first].letter);
				}
				d++;
			}

			int horizontalTemp = 0;
			bool otherHorizontalWords = false;

			int r = m.Plays[i].coordinates.first + 1;
			while (!board->isEmptySquare(m.Plays[i].coordinates.second, r)) {
				if (board->m_board[m.Plays[i].coordinates.second][r].blank == false) {
					horizontalTemp += tileLookUp->getScore(board->m_board[m.Plays[i].coordinates.second][r].letter);
				}
				r++;
				otherHorizontalWords = true;

			}

			int l = m.Plays[i].coordinates.first - 1;
			while (!board->isEmptySquare(m.Plays[i].coordinates.second, l)) {
				if (board->m_board[m.Plays[i].coordinates.second][l].blank == false) {
					horizontalTemp += tileLookUp->getScore(board->m_board[m.Plays[i].coordinates.second][l].letter);
				}
				l--;
				otherHorizontalWords = true;

			}
			if (m.Plays[i].Blank == false) {
				verticalTemp += tileLookUp->getScore(m.Plays[i].Letter) *
					board->m_board[m.Plays[i].coordinates.second][m.Plays[i].coordinates.first].getLetterMultiplier();

			}
			if (otherHorizontalWords) {
				if (m.Plays[i].Blank == false) {
					horizontalTemp += tileLookUp->getScore(m.Plays[i].Letter) *
						board->m_board[m.Plays[i].coordinates.second][m.Plays[i].coordinates.first].getLetterMultiplier();
				}

				horizontalTemp *= board->m_board[m.Plays[i].coordinates.second][m.Plays[i].coordinates.first].getWordMultiplier();
				score += horizontalTemp;
			}
			wordMult *= board->m_board[m.Plays[i].coordinates.second][m.Plays[i].coordinates.first].getWordMultiplier();

		}

		if (m.isBingo)
			score += 50;
		score  += verticalTemp * wordMult;
	}
	m.score = score;
	return score;
}

ScoreManager::~ScoreManager()
{
}
