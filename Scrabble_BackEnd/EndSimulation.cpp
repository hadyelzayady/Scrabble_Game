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
			myRack.getLeave(moves[i]);
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

unordered_map<int, vector<BStarNode>> cache;

vector<BStarNode> &getMoves(BStarNode node)
{
	//if (cache.find(node.id) != cache.end()) //node expabded before
	//{
	//	return cache[node.id];
	//}
	//if (node.id == 0)
	//{
	//	cache[0] = vector<BStarNode>({BStarNode(30, 15, 1), BStarNode(30, 16, 2), BStarNode(19, 10, 3)});
	//	return cache[0];
	//}
	//if (node.id == 1)
	//{
	//	cache[1] = vector<BStarNode>({BStarNode(15, 26, 4), BStarNode(19, 25, 5), BStarNode(22, 30, 6)});
	//	return cache[1];
	//}
	//if (node.id == 4)
	//{
	//	cache[4] = vector<BStarNode>({BStarNode(26, 22, 7)});
	//	return cache[4];
	//}
	//if (node.id == 5)
	//{
	//	cache[5] = vector<BStarNode>({BStarNode(25, 23, 8)});
	//	return cache[5];
	//}
	cache[node.id] = vector<BStarNode>({});
	return cache[node.id];
}
bool myfunctionmax(BStarNode i, BStarNode j) { return (i.optm > j.optm); }
bool myfunctionmin(BStarNode i, BStarNode j) { return (i.optm < j.optm); }

void getBest2MovesMax(vector<BStarNode> &moves, vector<BStarNode *> &best2nodes)
{
	sort(moves.begin(), moves.end(), myfunctionmax);

	if (moves.size() != 1)
	{
		//if 2 nodes have same optimistic values choose node with smallest range (best node)
		BStarNode *bestBStarNode = &moves[0];
		int i = 0;
		for (i = 0; i < moves.size() && moves[i].optm == moves[0].optm; i++)
		{
			if (moves[i].pess > bestBStarNode->pess)
				bestBStarNode = &moves[i];
		}
		best2nodes = {bestBStarNode};
		if (i < moves.size()) //second best node is the one just after the best one
			best2nodes.push_back(&moves[i]);
	}
	else
		best2nodes = {&moves[0]};
}
void getBest2MovesMin(vector<BStarNode> &moves, vector<BStarNode *> &best2moves)
{
	sort(moves.begin(), moves.end(), myfunctionmin);
	if (moves.size() != 1)
	{
		//if 2 nodes have same optimistic values choose node with smallest range (best node)
		BStarNode *bestBStarNode = &moves[0];
		int i = 0;
		for (i = 0; i < moves.size() && moves[i].optm == moves[0].optm; i++)
		{
			if (moves[i].pess < bestBStarNode->pess)
				bestBStarNode = &moves[i];
		}
		best2moves = {bestBStarNode};
		if (i < moves.size()) //second best node is the one just after the best one
			best2moves.push_back(&moves[i]);
	}
	else
		best2moves = {&moves[0]};
}
int getMaxPessimistic(vector<BStarNode> moves)
{
	int max = 0;
	for (size_t i = 0; i < moves.size(); i++)
	{
		if (moves[i].pess > max)
			max = moves[i].pess;
	}
	return max;
}
int getBestPessimisticMin(vector<BStarNode> moves)
{
	int min = 1000;
	for (size_t i = 0; i < moves.size(); i++)
	{
		if (moves[i].pess < min)
			min = moves[i].pess;
	}
	return min;
}

vector<BStarNode>* EndSimulation::getChildren(const BStarNode &node,Rack& rack)
{
	if (cache.find(node.id) != cache.end()) //node expanded before
	{
		return &cache[node.id]; //? check if children have the same vector by reference
	}
	//node first expand
	vector<Move> moves; //= getMoves(board, rack);
	vector<BStarNode>&cachevector = cache[node.id];
	//get max 2 moves
	for (size_t i = 0; i < moves.size(); i++)
	{
		//! improvement: not all nodes executed so ,board should not be created for all nodes ,just the 1st and 2nd node
		Board board(node.board);
		board.commitMove(moves[i]);
		int opt_pess[2] = { 1,2 };// getOptimPess();
		cachevector.push_back(BStarNode(opt_pess[0], opt_pess[1], cache.size(), board, moves[i]));
	}
	return &cachevector;
}
BStarNode EndSimulation::BStar(BStarNode &node, int depth, bool maximizingPlayer,Rack rack)
{
	while (maximizingPlayer)
	{
		vector<BStarNode>* branches;
		branches = getChildren(node, rack);
		if ((*branches).empty())
			return node;
		// heuristic is calculated for each move inside this function,!
		//!sorting according to only optimistic value
		vector<BStarNode *> bestFirstAndSecond;
		getBest2MovesMax((*branches), bestFirstAndSecond);		   //TODO: sort(index sorting) ,or use cache
		int maxOptimisticValue = bestFirstAndSecond[0]->optm;  //max perssimistic value
		int maxPessimisticValue = getMaxPessimistic(*branches); //max perssimistic value
		if (maxOptimisticValue < node.pess || maxPessimisticValue > node.optm)
		{
			//backup
			node.pess = maxOptimisticValue;
			node.optm = maxPessimisticValue;
			if (depth > 0)
				return BStarNode(-1, -1, -1, NULL,Move()); //TODO what to return
			//else depth=0
			if ((*branches).size() == 1 || maxPessimisticValue >= bestFirstAndSecond[1]->optm) //terminating condition
				return *bestFirstAndSecond[0];
		}
		if (depth == 0)//TODO: if max branch is finished parsing--> mark it as done and start expanding next node
		{
			Rack newrack = rack;
			newrack.removeMoveTiles(bestFirstAndSecond[0]->move);
			BStarNode x = BStar(*bestFirstAndSecond[0], depth + 1, false,newrack);
			if (x.id == -1)
				continue;
			else
				break;
		}
		else
		{
			Rack newrack = rack;
			newrack.removeMoveTiles(bestFirstAndSecond[0]->move);
			if (BStar(*bestFirstAndSecond[0], depth + 1, false,newrack).id == -1)
				continue;
			else
				break;
		}
	}
	while (!maximizingPlayer)
	{
		vector<BStarNode>* branches;
		branches = getChildren(node, rack);
		if ((*branches).empty())
			return node;
		// heuristic is calculated for each move inside this function,!
		//!sorting according to only optimistic value
		vector<BStarNode *> bestFirstAndSecond;
		getBest2MovesMin((*branches), bestFirstAndSecond);		   //TODO: sort(index sorting) ,or use cache
		int maxOptimisticValue = bestFirstAndSecond[0]->optm;	  //max perssimistic value
		int maxPessimisticValue = getBestPessimisticMin(*branches); //max perssimistic value
		if (maxOptimisticValue > node.pess || maxPessimisticValue < node.optm)
		{
			//backup
			node.pess = maxOptimisticValue;
			node.optm = maxPessimisticValue;
			if (depth > 0)
				return BStarNode(-1, -1, -1, NULL,Move()); //TODO what to return
			if (maxPessimisticValue >= bestFirstAndSecond[1]->optm)
				return *bestFirstAndSecond[0];
		}
		if (depth == 0)
		{
			Rack newrack = rack;
			newrack.removeMoveTiles(bestFirstAndSecond[0]->move);
			BStarNode x = BStar(*bestFirstAndSecond[0], depth + 1, true,newrack);
			if (x.id == -1)
				continue;
			else
				break;
		}
		else
		{
			Rack newrack = rack;
			newrack.removeMoveTiles(bestFirstAndSecond[0]->move);
			BStarNode x = BStar(*bestFirstAndSecond[0], depth + 1, true,newrack);
			if (x.id == -1)
			{
				continue;
			}
			else
				break;
		}
	}
}

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