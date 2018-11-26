﻿#include "EndSimulation.h"
#include <limits>
#include "Play.h"
#include "move.h"
#include <vector>
#include "Board.h"
#include <algorithm>
//EndSimulation::EndSimulation(Square board[ROWS_COUNT][COLUMNS_COUNT])
//{
//
//}
int EndSimulation::minimax(Board board, int score, int alpha, int beta, bool maximizingPlayer)
{
	////TODO:score is myscore-opponet score

	vector<Move> moves; //=getPlays()
	if (moves.empty())
		return score;
	if (maximizingPlayer)
	{
		int maxEval = INT_MIN;
		for (size_t i = 0; i < moves.size(); i++)
		{
			myRack.removeMoveTiles(moves[i]);
			int eval = minimax(board.commitMoveSimB(moves[i]), score + scoreManager->computeMoveScore(moves[i], &board), alpha, beta, false);
			int maxEval = max(maxEval, eval);
			int alpha = max(alpha, eval);
			if (beta <= alpha)
				break;
			return maxEval;
		}
	}
	else
	{

		int minEval = INT_MAX;
		for (size_t i = 0; i < moves.size(); i++)
		{
			opponetRack.removeMoveTiles(moves[i]);
			int eval = minimax(board.commitMoveSimB(moves[i]), score - scoreManager->computeMoveScore(moves[i], &board), alpha, beta, true);
			int minEval = min(minEval, eval);
			int beta = min(beta, eval);
			if (beta <= alpha)
				break;
			return minEval;
		}
	}
}
void EndSimulation::start()
{
}

EndSimulation::EndSimulation(const Board&board,ScoreManager * scoreManager, Rack opponentRack, Rack myRack)
{
	this->scoreManager = scoreManager;
	this->opponetRack = opponentRack;
	this->myRack = myRack;
	this->board=board;//! test implicit copy constructors

}
EndSimulation::~EndSimulation()
{
}
