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
	return pair<int, Move>();
	//////TODO:score is myscore-opponet score
	////! only start with max player
	//if (maximizingPlayer)
	//{
	//	//end condition
	//	vector<Move> moves = getplays();
	//	if (moves.empty())
	//	{
	//		Move move;
	//		return pair<int, Move>(score, move);
	//	}
	//	int maxEval = INT_MIN;
	//	Move move = moves[0];
	//	for (size_t i = 0; i < moves.size(); i++)
	//	{
	//		myRack.getLeave(moves[i]);
	//		//heruestic needs:
	//		pair<int, Move> eval_move = minimax(board.commitMoveSimB(moves[i]), score + ScoreManager::calculateScore(moves[i], board,tileLookup), alpha, beta, false);
	//		int eval = eval_move.first;

	//		if (maxEval < eval) //select best move with score
	//		{
	//			maxEval = eval;
	//			move = moves[i];
	//		}
	//		int _alpha = max(alpha, eval);
	//		if (beta <= _alpha)
	//			break;
	//	}
	//	return pair<int, Move>(maxEval, move);
	//}
	//else
	//{
	//	vector<Move> moves = getplays();
	//	if (moves.empty())
	//	{
	//		Move move;
	//		return pair<int, Move>(score, move);
	//	}
	//	int minEval = INT_MAX;
	//	Move move = moves[0];
	//	for (size_t i = 0; i < moves.size(); i++)
	//	{
	//		opponetRack.removeMoveTiles(moves[i]);
	//		pair<int, Move> eval_move = minimax(board.commitMoveSimB(moves[i]), score - ScoreManager::calculateScore(moves[i], board,tileLookup), alpha, beta, true);
	//		int eval = eval_move.first;

	//		if (minEval > eval) //select best move with score
	//		{
	//			minEval = eval;
	//			move = moves[i];
	//		}
	//		int _beta = min(beta, eval);
	//		if (_beta <= alpha)
	//			break;
	//	}
	//	return pair<int, Move>(minEval, move);
	//	;
	//}
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
		int bestOpenedNodeIndex = 0;
		if (moves[bestOpenedNodeIndex].closed)
		{
			//get first best optm
			for (int i = bestOpenedNodeIndex+1; i < moves.size(); i++)
			{
				if (!moves[i].closed)
				{
					bestBStarNode = &moves[i];
					bestOpenedNodeIndex = i;
					break;//we need only first unclosed node
				}
			}
		}
		int i = 0;
		//get node with optim=bestoptm but with smalled range
		for (i = bestOpenedNodeIndex; i < moves.size() && moves[i].optm == moves[bestOpenedNodeIndex].optm; i++)
		{
			if (moves[i].pess > bestBStarNode->pess && !moves[i].closed)// check smaller range
				bestBStarNode = &moves[i];
		}

		best2nodes = { bestBStarNode };
		if (i < moves.size()) //second best node is the one just after the best one
			best2nodes.push_back(&moves[i]);
	}
	else//only one move
		best2nodes = { &moves[0] };
}
//get best move when depth=0 and terminating condition not met with all branches visited
//return index of best move
int getBestMove(vector<BStarNode> &moves)
{
	if (moves.size() != 1)
	{
		//if 2 nodes have same optimistic values choose node with smallest range (best node)
		BStarNode *bestBStarNode = &moves[0];
		int bestNodeIndex = 0;
			//get first best optm
		for (int i = bestNodeIndex + 1; i < moves.size() && moves[i].optm==moves[0].optm; i++)
		{
			if (moves[i].pess > bestBStarNode->pess)// check smaller range
				bestNodeIndex;
		}
		return bestNodeIndex;
	}
	else
		return 0;
}
void getBest2MovesMin(vector<BStarNode> &moves, vector<BStarNode *> &best2moves)
{
	sort(moves.begin(), moves.end(), myfunctionmin);
	if (moves.size() != 1)
	{
		//if 2 nodes have same optimistic values choose node with smallest range (best node)
		BStarNode *bestBStarNode = &moves[0];
		int bestOpenedNodeIndex = 0;
		if (moves[bestOpenedNodeIndex].closed)
		{
			//get first best optm
			for (int i = bestOpenedNodeIndex + 1; i < moves.size(); i++)
			{
				if (!moves[i].closed)
				{
					bestBStarNode = &moves[i];
					bestOpenedNodeIndex = i;
					break;//we need only first unclosed node
				}
			}
		}
		int i = 0;
		//get node with optim=bestoptm but with smalled range
		for (i = bestOpenedNodeIndex; i < moves.size() && moves[i].optm == moves[bestOpenedNodeIndex].optm; i++)
		{
			if (moves[i].pess < bestBStarNode->pess && !moves[i].closed)// check smaller range
				bestBStarNode = &moves[i];
		}
		best2moves = { bestBStarNode };
		if (i < moves.size()) //second best node is the one just after the best one
			best2moves.push_back(&moves[i]);
	}
	else
		best2moves = {&moves[0]};
}
double getMaxPessimistic(vector<BStarNode> moves)
{
	double max = moves[0].pess;
	for (size_t i = 1; i < moves.size(); i++)
	{
		if (moves[i].pess > max)
			max = moves[i].pess;
	}
	return max;
}
double getBestPessimisticMin(vector<BStarNode> moves)
{
	double min = moves[0].pess;
	for (size_t i = 1; i < moves.size(); i++)
	{
		if (moves[i].pess < min)
			min = moves[i].pess;
	}
	return min;
}

vector<BStarNode>* EndSimulation::getChildren(const BStarNode &node,Rack& myrack,Rack&oprack, bool ismax, vector<BStarNode *>& bestFirstAndSecond)
{
	if (cache.find(node.id) != cache.end()) //node expanded before
	{
		//TODO:set bestfirstandsecond by iterating over cache vector and get max not closed nodes
		return &cache[node.id]; //? check if children have the same vector by reference
	}
	//node first expand
	vector<BStarNode>&cachevector = cache[node.id];
	BStarNode *bestBStarNode=NULL;
	BStarNode *alternBStarNode=NULL;
	//TODO: calc score with heuristic
	//get max 2 moves
	//max node
	//? what if all nodes have same optim value what altern will be?
	if (ismax) {
		vector<Move> moves = MG->findWords(myrack.getRackTiles(), board);
		double maxOptm = -1;
		double maxaltern = -2;
		for (size_t i = 0;i< moves.size(); i++)
		{
			//! improvement: not all nodes executed so ,board should not be created for all nodes ,just the 1st and 2nd node
			board.commitMove(moves[i]);//commit new move
			board.computeCrossSets( MG->root);
			double moveScore = ScoreManager::calculateScore(moves[i], board, tileLookup);
			double optm, pess;
			hr->endGame2vals(oprack.getRackTiles(),myRack, moves[i], {}, {}, optm, pess);
			BStarNode node(optm + moveScore, pess + moveScore, (int)cache.size() + (int)cachevector.size(), moves[i]);
			cachevector.push_back(node);
			if (optm > maxOptm)
			{
				maxOptm = optm;
				bestBStarNode = &cachevector.back();
			}
			else if (optm == maxOptm)
			{
				if (pess > bestBStarNode->pess)// check smaller range
					bestBStarNode = &cachevector.back();
			}
			else if (optm > maxaltern)
			{
				maxaltern = optm;
				alternBStarNode = &cachevector.back();
			}
			else if (optm == maxaltern)
			{
				if (pess > alternBStarNode->pess)// check smaller range
					alternBStarNode = &cachevector.back();
			}
			board.UnCommitMove(moves[i]);
			board.computeCrossSets( MG->root);
		}
	}
	else {

		vector<Move> moves = MG->findWords(oprack.getRackTiles(), board);
		for (size_t i = 0; i < moves.size(); i++)
		{
			double minOptm = DBL_MAX-1;
			double minaltern = DBL_MAX;
			//! improvement: not all nodes executed so ,board should not be created for all nodes ,just the 1st and 2nd node
			board.commitMove(moves[i]);
			board.computeCrossSets( MG->root);
			double moveScore = ScoreManager::calculateScore(moves[i], board, tileLookup);
			double optm, pess;
			hr->endGame2vals(oprack.getRackTiles(),myRack, moves[i], {}, {}, pess, optm);
			BStarNode node(optm+moveScore, pess+moveScore, (int)cache.size() + (int)cachevector.size(), moves[i]);
			cachevector.push_back(node);
			if (optm < minOptm)
			{
				minOptm = optm;
				bestBStarNode = &cachevector.back();
			}
			else if (optm == minOptm)
			{
				if (pess < bestBStarNode->pess)// check smaller range
					bestBStarNode = &cachevector.back();
			}
			else if (optm < minaltern) {//altern node
				minaltern = optm;
				alternBStarNode = &cachevector.back();
			}
			else if (optm == minaltern)
			{
				if (pess < alternBStarNode->pess)// check smaller range
					alternBStarNode = &cachevector.back();
			}
			board.UnCommitMove(moves[i]);
			board.computeCrossSets(MG->root);

		}
	}
	if (bestBStarNode != NULL)
		bestFirstAndSecond.push_back(bestBStarNode);
	if (alternBStarNode != NULL)
		bestFirstAndSecond.push_back(alternBStarNode);
	return &cachevector;
}
BStarNode EndSimulation::BStar(BStarNode &node, int depth, bool maximizingPlayer,Rack myrack,Rack oprack)
{
	while (maximizingPlayer)
	{
		vector<BStarNode>* branches;
		BStarNode*highestOptmWithSmalledRange=NULL;
		vector<BStarNode *> bestFirstAndSecond;
		branches = getChildren(node, myrack,oprack,true,bestFirstAndSecond);
		if ((*branches).empty())//node has no chilren
		{
				node.closed = true;
				return BStarNode();
		}
		else if (bestFirstAndSecond.empty() )
		{
			if (depth == 0)//all root children are closed without terminating condition met
			{
				return (*branches)[getBestMove(*branches)];
			}
			else {
				return BStarNode();//backup as all children are closed
			}
		}
		// heuristic is calculated for each move inside this function,!
		//!sorting according to only optimistic value
		 //TODO: sort(index sorting) ,or use cache
		double maxOptimisticValue = bestFirstAndSecond[0]->optm;  //max perssimistic value
		double maxPessimisticValue = getMaxPessimistic(*branches); //max perssimistic value
		if (maxOptimisticValue < node.pess || maxPessimisticValue > node.optm)
		{
			//backup
			node.pess = maxOptimisticValue;
			node.optm = maxPessimisticValue;
			if (depth > 0)
				return BStarNode(); //TODO what to return
			//else depth=0
			if (bestFirstAndSecond.size() == 1 || bestFirstAndSecond[0]->pess >= bestFirstAndSecond[1]->optm) //terminating condition
				return *bestFirstAndSecond[0];
		}
		//TODO: till now no diff between if and else code (possible removing of if condition)
		if (depth == 0)//TODO: if max branch is finished parsing--> mark it as done and start expanding next node
		{
			Rack newrack = myrack;
			newrack.removeMoveTiles(bestFirstAndSecond[0]->move);
			board.commitMove(bestFirstAndSecond[0]->move);
			board.computeCrossSets(MG->root);
			int id = BStar(*bestFirstAndSecond[0], depth + 1, false, newrack, oprack).id;
			board.UnCommitMove(bestFirstAndSecond[0]->move);
			board.computeCrossSets( MG->root);
			if ( id == -1)
				continue;
			else
				break;
		}
		else
		{
			Rack newrack = myrack;
			newrack.removeMoveTiles(bestFirstAndSecond[0]->move);
			board.commitMove(bestFirstAndSecond[0]->move);
			board.computeCrossSets( MG->root);
			int id = BStar(*bestFirstAndSecond[0], depth + 1, false, newrack, oprack).id;
			board.UnCommitMove(bestFirstAndSecond[0]->move);
			board.computeCrossSets( MG->root);
			if (id == -1)
				continue;
			else
				break;
		}
	}
	while (!maximizingPlayer)//min always starts in depth 1 (not working if min is depth 0
	{
		vector<BStarNode>* branches;
		vector<BStarNode *> bestFirstAndSecond;
		branches = getChildren(node, myrack,oprack,false, bestFirstAndSecond);
		if ((*branches).empty())
		{
				node.closed = true;
				return BStarNode();
		}
		else if (bestFirstAndSecond.empty())
		{
			if (depth == 0)//all root children are closed without terminating condition met
			{
				return (*branches)[getBestMove(*branches)];
			}
			else {
				return BStarNode();//backup as all children are closed
			}
		}
		// heuristic is calculated for each move inside this function,!
		//!sorting according to only optimistic value
		//getBest2MovesMin((*branches), bestFirstAndSecond);		   //TODO: sort(index sorting) ,or use cache
		double maxOptimisticValue = bestFirstAndSecond[0]->optm;	  //max perssimistic value
		double maxPessimisticValue = getBestPessimisticMin(*branches); //max perssimistic value
		if (maxOptimisticValue > node.pess || maxPessimisticValue < node.optm)
		{
			//backup
			node.pess = maxOptimisticValue;
			node.optm = maxPessimisticValue;
			if (depth > 0)
				return BStarNode(); //TODO what to return
			if (bestFirstAndSecond.size() == 1 || bestFirstAndSecond[0]->pess <= bestFirstAndSecond[1]->optm)
				return *bestFirstAndSecond[0];
		}
		if (depth == 0)
		{
			Rack newrack = oprack;
			newrack.removeMoveTiles(bestFirstAndSecond[0]->move);
			board.commitMove(bestFirstAndSecond[0]->move);
			board.computeCrossSets( MG->root);
			int id = BStar(*bestFirstAndSecond[0], depth + 1, true, myrack, newrack).id;
			board.UnCommitMove(bestFirstAndSecond[0]->move);
			board.computeCrossSets(MG->root);
			if (id == -1)
				continue;
			else
				break;
		}
		else
		{
			Rack newrack = oprack;
			newrack.removeMoveTiles(bestFirstAndSecond[0]->move);
			board.commitMove(bestFirstAndSecond[0]->move);
			board.computeCrossSets(MG->root);
			int id=BStar(*bestFirstAndSecond[0], depth + 1, true, myrack, newrack).id;
			board.UnCommitMove(bestFirstAndSecond[0]->move);
			board.computeCrossSets( MG->root);
			if (id== -1)
			{
				continue;
			}
			else
				break;
		}
	}
	return BStarNode();
}

Move EndSimulation::start()
{
	BStarNode root(-100, 100, 0, Move());
	return BStar(root, 0, true, myRack,opponetRack).move;
}


EndSimulation::EndSimulation(const Board &board, TileLookUp*tl, Rack opponentRack, Rack myRack, Gaddag * GD, Heuristics* hr)
{
	this->scoreManager = scoreManager;
	this->opponetRack = opponentRack;
	this->myRack = myRack;
	this->tileLookup = tl;
	this->board = board; //! test implicit copy constructors
	this->MG = GD;
	this->hr = hr;
}

EndSimulation::~EndSimulation()
{
}