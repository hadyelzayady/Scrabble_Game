#include <iostream>
#include "GameManager.h"
using namespace std;
class Board2 {
public:
	int value;
	void commitMove(int val) {
		value =val;
	}
	Board2(int val)
	{
		value = 0;
	}
	Board2() {}
};
class Rac {
public:
	string rack;
	void removeMoveTiles() {
		rack.pop_back();
	}
	Rac(string rack) {
		this->rack = rack;
	}
};
class BStarNod {
public:
	int optm;
	int pess;
	int id;
	Board2 board;//TODO :try passing by reference
	//?chnage
	bool closed = false;//node has been visited till end and no more visiting
	int move;
	BStarNod() {
		this->optm = -1;
		this->pess = -1;
		this->id = -1;
	}
	BStarNod(int opt, int pess, int id, Board2 board, int move) {
		this->optm = opt;
		this->pess = pess;
		this->id = id;
		this->board = board;
		this->move = move;
	}

};
unordered_map<int, vector<BStarNod>> cache;
bool myfunctionmax(BStarNod i, BStarNod j) { return (i.optm > j.optm); }
bool myfunctionmin(BStarNod i, BStarNod j) { return (i.optm < j.optm); }

void getBest2MovesMax(vector<BStarNod> &moves, vector<BStarNod *> &best2nodes)
{
	sort(moves.begin(), moves.end(), myfunctionmax);

	if (moves.size() != 1)
	{
		//if 2 nodes have same optimistic values choose node with smallest range (best node)
		BStarNod *bestBStarNod = &moves[0];
		int i = 0;
		for (i = 0; i < moves.size() && moves[i].optm == moves[0].optm; i++)
		{
			if (moves[i].pess > bestBStarNod->pess)
				bestBStarNod = &moves[i];
		}
		best2nodes = { bestBStarNod };
		if (i < moves.size()) //second best node is the one just after the best one
			best2nodes.push_back(&moves[i]);
	}
	else
		best2nodes = { &moves[0] };
}
void getBest2MovesMin(vector<BStarNod> &moves, vector<BStarNod *> &best2moves)
{
	sort(moves.begin(), moves.end(), myfunctionmin);
	if (moves.size() != 1)
	{
		//if 2 nodes have same optimistic values choose node with smallest range (best node)
		BStarNod *bestBStarNod = &moves[0];
		int i = 0;
		for (i = 0; i < moves.size() && moves[i].optm == moves[0].optm; i++)
		{
			if (moves[i].pess < bestBStarNod->pess)
				bestBStarNod = &moves[i];
		}
		best2moves = { bestBStarNod };
		if (i < moves.size()) //second best node is the one just after the best one
			best2moves.push_back(&moves[i]);
	}
	else
		best2moves = { &moves[0] };
}
vector<int> getMoves()
{
	int movesize = rand() % 4 + 2;
	vector<int> moves;
	for (size_t i = 0; i < movesize; i++)
	{
		moves.push_back(rand() % 100);
	}
	return moves;
}

vector<BStarNod>* getChildren(const BStarNod &node, Rac& rac,bool ismax)
{
	if (cache.find(node.id) != cache.end()) //node expanded before
	{
		return &cache[node.id]; //? check if children have the same vector by reference
	}
	//node first expand
	vector<int> moves=getMoves();//=MG->findWords(rack.getLeave(rack), board);
	vector<BStarNod>&cachevector = cache[node.id];
	//get max 2 moves
	for (size_t i = 0; i < moves.size(); i++)
	{
		//! improvement: not all nodes executed so ,board should not be created for all nodes ,just the 1st and 2nd node
		Board2 board(node.board);
		board.commitMove(moves[i]);
		int optm,pess;
		if (ismax) {
			 optm =( rand()*rand()) % 100 +10;
			 pess = (rand()*rand()) % optm;
		}
		else {
			pess = (rand()*rand()) % 100+10;
			optm = (rand()*rand()) % pess;
		}
		cachevector.push_back(BStarNod(optm, pess, cache.size()+cachevector.size(), board, moves[i]));
	}
	return &cachevector;
}
int getMaxPessimistic(vector<BStarNod> moves)
{
	int max = 0;
	for (size_t i = 0; i < moves.size(); i++)
	{
		if (moves[i].pess > max)
			max = moves[i].pess;
	}
	return max;
}
int getBestPessimisticMin(vector<BStarNod> moves)
{
	int min = 1000;
	for (size_t i = 0; i < moves.size(); i++)
	{
		if (moves[i].pess < min)
			min = moves[i].pess;
	}
	return min;
}
BStarNod BStar(BStarNod &node, int depth, bool maximizingPlayer, Rac myrack,Rac oprack)
{
	while (maximizingPlayer)
	{
		vector<BStarNod>* branches;
		branches = getChildren(node, myrack,true);
		if ((*branches).empty())
		{
			//?change
			node.closed = true;
			return node;
		}
		// heuristic is calculated for each move inside this function,!
		//!sorting according to only optimistic value
		vector<BStarNod *> bestFirstAndSecond;
		getBest2MovesMax((*branches), bestFirstAndSecond);		   //TODO: sort(index sorting) ,or use cache
		int maxOptimisticValue = bestFirstAndSecond[0]->optm;  //max perssimistic value
		int maxPessimisticValue = getMaxPessimistic(*branches); //max perssimistic value
		if (maxOptimisticValue < node.pess || maxPessimisticValue > node.optm)
		{
			//backup
			node.pess = maxOptimisticValue;
			node.optm = maxPessimisticValue;
			if (depth > 0)
				return BStarNod(); //TODO what to return
			//else depth=0
			if ((*branches).size() == 1 || bestFirstAndSecond[0]->pess >= bestFirstAndSecond[1]->optm) //terminating condition
				return *bestFirstAndSecond[0];
		}
		if (depth == 0)//TODO: if max branch is finished parsing--> mark it as done and start expanding next node
		{
			Rac newrack = myrack;
			newrack.removeMoveTiles();
			BStarNod x = BStar(*bestFirstAndSecond[0], depth + 1, false, newrack,oprack);
			if (x.id == -1)
				continue;
			else
				break;
		}
		else
		{
			Rac newrack = myrack;
			newrack.removeMoveTiles();
			if (BStar(*bestFirstAndSecond[0], depth + 1, false, newrack,oprack).id == -1)
				continue;
			else
				break;
		}
	}
	while (!maximizingPlayer)
	{
		vector<BStarNod>* branches;
		branches = getChildren(node, oprack,false);
		if ((*branches).empty())
			return node;
		// heuristic is calculated for each move inside this function,!
		//!sorting according to only optimistic value
		vector<BStarNod *> bestFirstAndSecond;
		getBest2MovesMin((*branches), bestFirstAndSecond);		   //TODO: sort(index sorting) ,or use cache
		int maxOptimisticValue = bestFirstAndSecond[0]->optm;	  //max perssimistic value
		int maxPessimisticValue = getBestPessimisticMin(*branches); //max perssimistic value
		if (maxOptimisticValue > node.pess || maxPessimisticValue < node.optm)
		{
			//backup
			node.pess = maxOptimisticValue;
			node.optm = maxPessimisticValue;
			if (depth > 0)
				return BStarNod(); //TODO what to return
			if (bestFirstAndSecond[0]->pess >= bestFirstAndSecond[1]->optm)
				return *bestFirstAndSecond[0];
		}
		if (depth == 0)
		{
			Rac newrack = oprack;
			newrack.removeMoveTiles();
			BStarNod x = BStar(*bestFirstAndSecond[0], depth + 1, true,myrack ,newrack);
			if (x.id == -1)
				continue;
			else
				break;
		}
		else
		{
			Rac newrack = oprack;
			newrack.removeMoveTiles();
			BStarNod x = BStar(*bestFirstAndSecond[0], depth + 1, true, myrack,newrack);
			if (x.id == -1)
			{
				continue;
			}
			else
				break;
		}
	}
}
int main()
{
	Rac myrack("rack1");
	Rac oprack("rack2");
	BStarNod root(INT_MIN, INT_MAX, 0, Board2(0), 0);
	BStarNod best=BStar(root, 0, true, myrack, oprack);
	//string * playerNames;
	//int playerCount = 2;
	//playerNames = new string[playerCount];
	//playerNames[0] = "Scrabby-Do";
	//playerNames[1] = "Enemy";
	//Rack* r = new Rack();
	//r->addTile('A');
	//r->addTile('N');
	//r->addTile('B');
	//r->addTile('S');
	//r->addTile('D');
	//r->addTile('E');
	//r->addTile('F');
	//char c[] = { 'G','Z','Y','X' };
	//ProbabilityManager * Pm = new ProbabilityManager();
	//Board2 *B = new Board2();
	//Move* M = new Move();
	//Play *P = new Play();
	//P->set_Coordinates(make_pair(2, 3));
	//P->set_Letter('A', 1);
	//M->addPlay(*P);
	//B->commitMove(*M);
	//P->set_Coordinates(make_pair(4,5));
	//P->set_Letter('Z', 2);
	//Move* z = new Move();
	//z->addPlay(*P);
	//Board2 V = Board2::commitMoveSim(*z, *B);

	
//	MonteCarlo * M = new MonteCarlo(r,c,Pm);
	// M->simulation(100);
//	 Utilities * u =new  Utilities();
/*
	Intiating  instance tileLookUp from TileLookUp class
	*/
	//TileLookUp * tileLookUp = new TileLookUp();
	//GameManager * gameManager = new GameManager(tileLookUp, playerCount, playerNames);
	//gameManager->simulateGame();
	system("pause");
	return 0;
} 