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
vector<Move> EndSimulation::getplays()
{
	if (i == 3)
	{
		vector<Move> m(0);
		return m;
	}
	if (i % 2 == 0)
	{
		++i;
		return mymoves;
	}
	++i;
	return opmoves;
}
pair<int, Move> EndSimulation::minimax(Board board, int score, int alpha, int beta, bool maximizingPlayer)
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
		Move move = moves[0];
		for (size_t i = 0; i < moves.size(); i++)
		{
			myRack.removeMoveTiles(moves[i]);
			//heruestic needs:
			pair<int, Move> eval_move = minimax(board.commitMoveSimB(moves[i]), score + scoreManager->computeMoveScore(moves[i], &board), alpha, beta, false);
			int eval = eval_move.first;

			if (maxEval < eval) //select best move with score
			{
				maxEval = eval;
				move = moves[i];
			}
			int _alpha = max(alpha, eval);
			if (beta <= _alpha)
				break;
		}
		return pair<int, Move>(maxEval, move);
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

			if (minEval > eval) //select best move with score
			{
				minEval = eval;
				move = moves[i];
			}
			int _beta = min(beta, eval);
			if (_beta <= alpha)
				break;
		}
		return pair<int, Move>(minEval, move);
		;
	}
}
//Move EndSimulation::BStar(Board board, int &optimistic, int &pessimistic, int depth, bool maximizingPlayer)
//{
//	if (maximizingPlayer)
//	{
//		vector<Move> moves = getMoves(board, myRack); //TODO:use map to get moves if node expanded before without searching again
//		// heuristic is calculated for each move inside this function,!
//		//!sorting according to only optimistic value
//		pair<Move, pair<int, int>> bestFirstAndSecond[2] = getBest2MovesMax(moves); //TODO: sort(index sorting) ,or use cache
//		Move &bestMove = bestFirstAndSecond[0].first;
//		pair<int, int> &bestMoveOptimisticPessimistic = bestFirstAndSecond[0].second;
//		Move &alternMove = bestFirstAndSecond[1].first;
//		pair<int, int> &alternOptimisticPessimistic = bestFirstAndSecond[1].second;
//		int maxOptimisticValue = bestMoveOptimisticPessimistic.first; //max perssimistic value
//		int maxPessimisticValue = getMaxPessimistic(moves);			  //max perssimistic value
//		if (maxOptimisticValue < pessimistic || maxPessimisticValue > optimistic)
//		{
//			//backup
//			pessimistic = maxOptimisticValue;
//			optimistic = maxPessimisticValue;
//			if (depth > 0)
//				return; //TODO what to return
//			if (maxPessimisticValue >= alternOptimisticPessimistic.first)
//				return bestMove;
//		}
//		if (depth == 0)
//		{
//			if (maxPessimisticValue == bestMoveOptimisticPessimistic.second)
//				return BStar(commitMoveSimB(alternMove), alternOptimisticPessimistic.first, alternOptimisticPessimistic.second, depth + 1, false);
//			else
//				return BStar(commitMoveSimB(bestMove), bestMoveOptimisticPessimistic.first, bestMoveOptimisticPessimistic.second, depth + 1, false);
//		}
//		else
//		{
//			return BStar(commitMoveSimB(bestMove), bestMoveOptimisticPessimistic.first, bestMoveOptimisticPessimistic.second, depth + 1, false);
//		}
//	}
//	else
//	{
//		vector<Move> moves = getMoves(board, myRack); //TODO:use map to get moves if node expanded before without searching again
//		// heuristic is calculated for each move inside this function,!
//		//!sorting according to only optimistic value
//		pair<Move, pair<int, int>> bestFirstAndSecond[2] = getBest2MovesMax(moves); //TODO: sort(index sorting) ,or use cache
//		Move &bestMove = bestFirstAndSecond[0].first;
//		pair<int, int> &bestMoveOptimisticPessimistic = bestFirstAndSecond[0].second;
//		Move &alternMove = bestFirstAndSecond[1].first;
//		pair<int, int> &alternOptimisticPessimistic = bestFirstAndSecond[1].second;
//		int maxOptimisticValue = bestMoveOptimisticPessimistic.first; //max perssimistic value
//		int maxPessimisticValue = getMaxPessimistic(moves);			  //min perssimistic value(best pess value in min node)
//		if (maxOptimisticValue > pessimistic || maxPessimisticValue < optimistic)
//		{
//			//backup
//			pessimistic = maxOptimisticValue;
//			optimistic = maxPessimisticValue;
//			if (depth > 0)
//				return; //TODO what to return
//			if (maxPessimisticValue >= alternOptimisticPessimistic.first)
//				return bestMove;
//		}
//		if (depth == 0)
//		{
//			if (maxPessimisticValue == bestMoveOptimisticPessimistic.second)
//				return BStar(commitMoveSimB(alternMove), alternOptimisticPessimistic.first, alternOptimisticPessimistic.second, depth + 1, true);
//			else
//				return BStar(commitMoveSimB(bestMove), bestMoveOptimisticPessimistic.first, bestMoveOptimisticPessimistic.second, depth + 1, true);
//		}
//		else
//		{
//			return BStar(commitMoveSimB(bestMove), bestMoveOptimisticPessimistic.first, bestMoveOptimisticPessimistic.second, depth + 1, true);
//		}
//	}
//}
pair<int, Move> EndSimulation::start()
{
	return minimax(board, 0, INT_MIN, INT_MAX, true);
}

EndSimulation::EndSimulation(const Board &board, ScoreManager *scoreManager, Rack opponentRack, Rack myRack)
{
	this->scoreManager = scoreManager;
	this->opponetRack = opponentRack;
	this->myRack = myRack;
	this->board = board; //! test implicit copy constructors
}

EndSimulation::EndSimulation(const Board &board, ScoreManager *scoreManager, Rack opponentRack, Rack myRack, vector<Move> opmoves, vector<Move> mymoves)
{
	this->scoreManager = scoreManager;
	this->opponetRack = opponentRack;
	this->myRack = myRack;
	this->board = board; //! test implicit copy constructors
	this->mymoves = mymoves;
	this->opmoves = opmoves;
}
EndSimulation::~EndSimulation()
{
}
