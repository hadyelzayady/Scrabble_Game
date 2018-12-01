#include "EndSimulation.h"
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
/*
vector<Move> EndSimulation::getplays()
{
	if (i == 3)
	{
		vector<Move> m(0);
		return m;
	}
	if (i %2 ==0)
	{
		++i;
		return mymoves;
	}
	++i;
	return opmoves;

}
pair<int,Move> EndSimulation::minimax(Board board, int score, int alpha, int beta, bool maximizingPlayer)
{
	////TODO:score is myscore-opponet score
	//! only start with max player

	if (maximizingPlayer)
	{
		//end condition
		vector<Move> moves = getplays();
		if (moves.empty())
		{
			Move move;
			return pair<int, Move>(score, move);
		}
		int maxEval = INT_MIN;
		Move move=moves[0];
		for (size_t i = 0; i < moves.size(); i++)
		{
			myRack.getLeave(moves[i]);
			//heruestic needs:
			pair<int,Move> eval_move = minimax(board.commitMoveSimB(moves[i]), score + scoreManager->computeMoveScore(moves[i], &board), alpha, beta, false);
			int eval = eval_move.first;

			if (maxEval < eval)//select best move with score
			{
				maxEval = eval;
				move = moves[i];
			}
			int _alpha = max(alpha, eval);
			if (beta <= _alpha)
				break;
		}
		return pair<int,Move>(maxEval,move);

	}
	else
	{
		vector<Move> moves = getplays();
		if (moves.empty())
		{
			Move move;
			return pair<int, Move>(score, move);
		}
		int minEval = INT_MAX;
		Move move = moves[0];

		for (size_t i = 0; i < moves.size(); i++)
		{
			opponetRack.removeMoveTiles(moves[i]);
			pair<int, Move> eval_move = minimax(board.commitMoveSimB(moves[i]), score - scoreManager->computeMoveScore(moves[i], &board), alpha, beta, true);
			int eval = eval_move.first;

			if (minEval > eval)//select best move with score
			{
				minEval = eval;
				move = moves[i];
			}
			int _beta = min(beta, eval);
			if (_beta <= alpha)
				break;
		}
		return pair<int, Move>(minEval, move);;

	}
}
pair<int, Move> EndSimulation::start()
{
	return minimax(board, 0, INT_MIN, INT_MAX, true);
}

EndSimulation::EndSimulation(const Board&board,ScoreManager * scoreManager, Rack opponentRack, Rack myRack)
{
	this->scoreManager = scoreManager;
	this->opponetRack = opponentRack;
	this->myRack = myRack;
	this->board=board;//! test implicit copy constructors

}

EndSimulation::EndSimulation(const Board & board, ScoreManager * scoreManager, Rack opponentRack, Rack myRack, vector<Move> opmoves, vector<Move> mymoves)
{
	this->scoreManager = scoreManager;
	this->opponetRack = opponentRack;
	this->myRack = myRack;
	this->board = board;//! test implicit copy constructors
	this->mymoves = mymoves;
	this->opmoves = opmoves;
}
EndSimulation::~EndSimulation()
{
}
*/