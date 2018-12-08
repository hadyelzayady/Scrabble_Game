#include "EndSimulation.h"
#include <limits>
#include "Play.h"
#include "move.h"
#include <vector>
#include "Board.h"
#include <algorithm>


bool myfunctionmax(BStarNode i, BStarNode j) { return (i.optm > j.optm); }
bool myfunctionmin(BStarNode i, BStarNode j) { return (i.optm < j.optm); }


//get best move when depth=0 and terminating condition not met with all branches visited
//return index of best move
int getBestMove(vector<BStarNode> &moves)
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
void getBestFirstAndSecondMax(vector<BStarNode>&moves, vector<BStarNode *>& bestFirstAndSecond)
{
	double maxOptm = -1;
	double maxaltern = -2;
	BStarNode *bestBStarNode = NULL;
	BStarNode *alternBStarNode = NULL;
	for (size_t i = 0; i < moves.size(); i++)
	{
		if (!moves[i].closed)
		{
			if (moves[i].optm > maxOptm)
			{
				maxOptm = moves[i].optm;
				bestBStarNode = &moves[i];
			}
			else if (moves[i].optm == maxOptm)
			{
				if (moves[i].pess > bestBStarNode->pess)// check smaller range
					bestBStarNode = &moves[i];
			}
			else if (moves[i].optm > maxaltern)
			{
				maxaltern = moves[i].optm;
				alternBStarNode = &moves[i];
			}
			else if (moves[i].optm == maxaltern)
			{
				if (moves[i].optm > alternBStarNode->pess)// check smaller range
					alternBStarNode = &moves[i];
			}
		}
	}
	if (bestBStarNode != NULL)
		bestFirstAndSecond.push_back(bestBStarNode);
	if (alternBStarNode != NULL)
		bestFirstAndSecond.push_back(alternBStarNode);

}
void getBestFirstAndSecondMin(vector<BStarNode>&moves, vector<BStarNode *>& bestFirstAndSecond)
{
	double minOptm = DBL_MAX - 1;
	double minaltern = DBL_MAX;
	BStarNode *bestBStarNode = NULL;
	BStarNode *alternBStarNode = NULL;
	for (size_t i = 0; i < moves.size(); i++)
	{
		if (!moves[i].closed)
		{
			if (moves[i].optm < minOptm)
			{
				minOptm = moves[i].optm;
				bestBStarNode = &moves[i];
			}
			else if (moves[i].optm == minOptm)
			{
				if (moves[i].pess < bestBStarNode->pess)// check smaller range
					bestBStarNode = &moves[i];
			}
			else if (moves[i].optm < minaltern) {//altern node
				minaltern = moves[i].optm;
				alternBStarNode = &moves[i];
			}
			else if (moves[i].optm == minaltern)
			{
				if (moves[i].pess < alternBStarNode->pess)// check smaller range
					alternBStarNode = &moves[i];
			}
		}
	}
	if (bestBStarNode != NULL)
		bestFirstAndSecond.push_back(bestBStarNode);
	if (alternBStarNode != NULL)
		bestFirstAndSecond.push_back(alternBStarNode);

}
vector<BStarNode>* EndSimulation::getChildren(const BStarNode &node,Rack& myrack,Rack&oprack, bool ismax, vector<BStarNode *>& bestFirstAndSecond)
{
	if (cache.find(node.id) != cache.end()) //node expanded before
	{
		//TODO:set bestfirstandsecond by iterating over cache vector and get max not closed nodes
		vector<BStarNode>& moves = cache[node.id];
		if(ismax)
			getBestFirstAndSecondMax(moves,bestFirstAndSecond);
		else
			getBestFirstAndSecondMin(moves, bestFirstAndSecond);
		//
		return &cache[node.id]; //? check if children have the same vector by reference
	}
	//node first expand
	vector<BStarNode>&cachevector = cache[node.id];
	int bestBStarNodeindex=-1;
	int alternBStarNodeindex=-1;
	//TODO: calc score with heuristic
	//get max 2 moves
	//max node
	//? what if all nodes have same optim value what altern will be?
	if (ismax) {
		vector<Move> moves = MG->findWords(myrack.getRackTiles(), board);
		double maxOptm = -10000;
		double maxaltern = -2000000;
		for (size_t i = 0;i< moves.size(); i++)
		{
			//! improvement: not all nodes executed so ,board should not be created for all nodes ,just the 1st and 2nd node
			board.commitMove(moves[i]);//commit new move
			double moveScore = ScoreManager::calculateScore(moves[i], board, tileLookup);
			double optm, pess;
			hr->endGame2vals(oprack.getRackTiles(),myRack, moves[i], {}, {}, optm, pess);
			optm += moveScore;
			pess += moveScore;
			BStarNode tempnode(optm, pess, (int)cache.size() + (int)cachevector.size(), moves[i]);
			cachevector.push_back(tempnode);
			if (optm > maxOptm)
			{
				maxOptm = optm;
				bestBStarNodeindex = cachevector.size()-1;
			}
			else if (optm == maxOptm)
			{
				if (pess > cachevector[bestBStarNodeindex].pess)// check smaller range
					bestBStarNodeindex = cachevector.size() - 1;
			}
			else if (optm > maxaltern)
			{
				maxaltern = optm;
				alternBStarNodeindex = cachevector.size() - 1;
			}
			else if (optm == maxaltern)
			{
				if (pess > cachevector[alternBStarNodeindex].pess)// check smaller range
					alternBStarNodeindex = cachevector.size() - 1;
			}
			board.UnCommitMove(moves[i]);
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
			double moveScore = ScoreManager::calculateScore(moves[i], board, tileLookup);
			double optm, pess;
			hr->endGame2vals(oprack.getRackTiles(),myRack, moves[i], {}, {}, pess, optm);
			pess += pess;
			optm += optm;
			BStarNode tempnode(optm, pess, (int)cache.size() + (int)cachevector.size(), moves[i]);
			cachevector.push_back(tempnode);
			if (optm < minOptm)
			{
				minOptm = optm;
				bestBStarNodeindex = cachevector.size() - 1;
			}
			else if (optm == minOptm)
			{
				if (pess < cachevector[bestBStarNodeindex].pess)// check smaller range
					bestBStarNodeindex = cachevector.size() - 1;
			}
			else if (optm < minaltern) {//altern node
				minaltern = optm;
				alternBStarNodeindex = cachevector.size() - 1;
			}
			else if (optm == minaltern)
			{
				if (pess < cachevector[alternBStarNodeindex].pess)// check smaller range
					alternBStarNodeindex = cachevector.size() - 1;
			}
			board.UnCommitMove(moves[i]);

		}
	}
	if (bestBStarNodeindex != -1)
		bestFirstAndSecond.push_back(&cachevector[bestBStarNodeindex]);
	if (alternBStarNodeindex != -1)
		bestFirstAndSecond.push_back(&cachevector[alternBStarNodeindex]);
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
				node.closed = true;
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