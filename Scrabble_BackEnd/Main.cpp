#include <iostream>
#include "GameManager.h"
#include <fstream>
#include <iostream>
#include <string>
#include "EndSimulation.h"
#include "ScoreManager.h"
#include <vector>
#include <algorithm>
using namespace std;
//Move createMove(string line, bool h)
//{
//	cout << line;
//	char *word = strtok(&line[0], " ");
//	char *row = strtok(&line[strlen(word) + 1], " ");
//	char *col = strtok(&line[strlen(word) + strlen(row) + 2], " ");
//	Move move;
//	//stoi does not work propery
//	// opponent moves are vertical
//	if (h)
//	{
//		for (size_t i = 0; i < strlen(word); i++)
//		{
//			int r = atoi(row);
//			int c = atoi(col);
//			Play play(r, c + i, word[i], false);
//			move.addPlay(play);
//		}
//	}
//	else
//	{
//		for (size_t i = 0; i < strlen(word); i++)
//		{
//			int r = atoi(row);
//			int c = atoi(col);
//			Play play(r + i, c, word[i], false);
//			move.addPlay(play);
//		}
//	}
//
//	return move;
//}
//Board parsefile(vector<Move> &mymoves, vector<Move> &opmoves)
//{
//	string line;
//	ifstream myfile("board_status.txt");
//	Board board;
//	if (myfile.is_open())
//	{
//		for (size_t i = 0; i < 15; i++)
//		{
//			getline(myfile, line);
//			for (size_t j = 0; j < 15; j++)
//			{
//				if (line[j] != '*')
//					board.m_board[i][j].letter = line[j];
//			}
//		}
//		for (size_t i = 0; i < 6; i++)
//		{
//			getline(myfile, line);
//			Move move = createMove(line, true);
//			mymoves.push_back(move);
//		}
//		for (size_t i = 0; i < 3; i++)
//		{
//			getline(myfile, line);
//			Move move = createMove(line, false);
//			opmoves.push_back(move);
//		}
//		myfile.close();
//	}
//
//	return board;
//}
class Node
{
public:
	int optm;
	int pess;
	int id;
	Node(int opt, int pess, int id) {
		this->optm = opt;
		this->pess = pess;
		this->id = id;
	}
};
unordered_map < int, vector<Node>> cache;

vector<Node>& getMoves(Node node)
{
	if (cache.find(node.id) != cache.end())//node expabded before
	{
		return cache[node.id];
	}
	if (node.id == 0)
	{
		cache[0] = vector<Node>({ Node(30,15,1),Node(30,16,2),Node(19,10,3) });
		return cache[0];
	}
	if (node.id == 1)
	{
		cache[1]=vector<Node>({ Node(15,26,4),Node(19,25,5),Node(22,30,6) });
		return cache[1];
	}
	if (node.id == 4)
	{
		cache[4]=vector<Node>({ Node(26,22,7) });
		return cache[4];
	}
	if (node.id == 5)
	{
		cache[5]=vector<Node>({ Node(25,23,8) });
		return cache[5];
	}
	cache[node.id]=vector<Node>({	});
	return cache[node.id];
}
bool myfunctionmax(Node i, Node j) { return (i.optm > j.optm); }
bool myfunctionmin(Node i, Node j) { return (i.optm < j.optm); }

void getBest2MovesMax(vector<Node>& moves, vector<Node*>&best2moves)
{
	sort(moves.begin(), moves.end(), myfunctionmax);

	if (moves.size() != 1)
	{
		//if 2 nodes have same optimistic values choose node with smallest range (best node)
		Node& bestNode = moves[0];
		int i = 0;
		for ( i = 0; i < moves.size() && moves[i].optm == moves[0].optm; i++)
		{
			if (moves[i].pess > bestNode.pess)
				bestNode = moves[i];
		}
		best2moves = { &bestNode };
		if (i < moves.size())//second best node is the one just after the best one 
			best2moves.push_back(&moves[i]);
	}
	else 
		best2moves = { &moves[0] };
}
void getBest2MovesMin(vector<Node>& moves,vector<Node*>&best2moves)
{
	sort(moves.begin(), moves.end(), myfunctionmin);
	if (moves.size() != 1)
	{
		//if 2 nodes have same optimistic values choose node with smallest range (best node)
		Node& bestNode = moves[0];
		int i = 0;
		for (i = 0; i < moves.size() && moves[i].optm == moves[0].optm; i++)
		{
			if (moves[i].pess < bestNode.pess)
				bestNode = moves[i];
		}
		best2moves = { &bestNode };
		if (i < moves.size())//second best node is the one just after the best one 
			best2moves.push_back(&moves[i]);
	}
	else
		best2moves = { &moves[0] };
}
int getMaxPessimistic(vector<Node>moves)
{
	int max = 0;
	for (size_t i = 0; i < moves.size(); i++)
	{
		if (moves[i].pess > max)
			max = moves[i].pess;
	}
	return max;
}
int getBestPessimisticMin(vector<Node>moves)
{
	int min = 1000;
	for (size_t i = 0; i < moves.size(); i++)
	{
		if (moves[i].pess < min)
			min = moves[i].pess;
	}
	return min;
}
Node BStar(Node& node, int depth, bool maximizingPlayer)
{
	while (maximizingPlayer )
	{
		vector<Node>&branches = getMoves(node); //TODO:use map to get moves if node expanded before without searching again
		if (branches.empty())
			return node;
									  // heuristic is calculated for each move inside this function,!
		//!sorting according to only optimistic value
		vector<Node*> bestFirstAndSecond;
		getBest2MovesMax(branches,bestFirstAndSecond); //TODO: sort(index sorting) ,or use cache
		int maxOptimisticValue = bestFirstAndSecond[0]->optm; //max perssimistic value
		int maxPessimisticValue = getMaxPessimistic(branches);			  //max perssimistic value
		if (maxOptimisticValue < node.pess || maxPessimisticValue > node.optm)
		{
			//backup
			node.pess = maxOptimisticValue;
			node.optm = maxPessimisticValue;
			if (depth > 0)
				return Node(-1,-1,-1); //TODO what to return
			//else depth=0 
			if (branches.size()==1 || maxPessimisticValue >= bestFirstAndSecond[1]->optm)//terminating condition
				return *bestFirstAndSecond[0];
		}
		if (depth == 0)
		{
			Node x = BStar(*bestFirstAndSecond[0], depth + 1, false);
			if (x.id == -1)
				continue;
			else
				break;
		}
		else
		{
			if (BStar(*bestFirstAndSecond[0], depth + 1, false).id == -1)
				continue;
			else
				break;
		}
	}
	while(!maximizingPlayer)
	{
		vector<Node>&branches = getMoves(node); //TODO:use map to get moves if node expanded before without searching again

		if (branches.empty())
			return node;
												// heuristic is calculated for each move inside this function,!
		//!sorting according to only optimistic value
		vector<Node*> bestFirstAndSecond;
		getBest2MovesMin(branches, bestFirstAndSecond); //TODO: sort(index sorting) ,or use cache
		int maxOptimisticValue = bestFirstAndSecond[0]->optm; //max perssimistic value
		int maxPessimisticValue = getBestPessimisticMin(branches);			  //max perssimistic value
		if (maxOptimisticValue > node.pess || maxPessimisticValue < node.optm)
		{
			//backup
			node.pess = maxOptimisticValue;
			node.optm = maxPessimisticValue;
			if (depth > 0)
				return Node(-1, -1, -1); //TODO what to return
			if (maxPessimisticValue >= bestFirstAndSecond[1]->optm)
				return *bestFirstAndSecond[0];
		}
		if (depth == 0)
		{
			int id = BStar(*bestFirstAndSecond[0], depth + 1, true).id;
			if (id == -1)
				continue;
			else
				break;
		}
		else
		{
			Node x = BStar(*bestFirstAndSecond[0], depth + 1, true);
			if (x.id == -1) {
				continue;
			}
			else
				break;
		}
	}
}
int main()
{
	Node root(INT_MIN, INT_MAX, 0);
	//Node best=BStar(root, 0, true);
	////(test commitmove and commitMoveSim
	//Move move;
	//Play play;
	//play.set_Letter('A', 1);
	//play.set_Coordinates(pair<int, int>(7, 6));
	//move.addPlay(play);
	//Board b = board.commitMoveSimB(move);
	//play.set_Letter('Z', 1);
	//move.addPlay(play);
	//board.commitMove(move);
	//////////
	//vector<Move> mymoves,opmoves;
	//Board board = parsefile(mymoves,opmoves);
	//TileLookUp til;
	//ScoreManager sc(&board,&til);
	//Rack myrack("ENDWISE"), oprack("BOUWKAF");
	//EndSimulation end(board,&sc,oprack,myrack,opmoves,mymoves);
	//pair<int,Move> bestmove=end.start();
	//////

	//////
	//string *playerNames;
	//int playerCount = 2;
	//playerNames = new string[playerCount];
	//playerNames[0] = "Scrabby-Do";
	//playerNames[1] = "Enemy";
	//Rack *r = new Rack();
	//r->addTile('A');
	//r->addTile('N');
	//r->addTile('B');
	//r->addTile('S');
	//r->addTile('D');
	//r->addTile('E');
	//r->addTile('F');
	//char c[] = {'G', 'Z', 'Y', 'X'};
	//ProbabilityManager *Pm = new ProbabilityManager();
	//MonteCarlo *M = new MonteCarlo(r, c, Pm);
	//M->simulation(100);
	//Utilities *u = new Utilities();
	///*
	// Intiating  instance tileLookUp from TileLookUp class
	// */
	//TileLookUp * tileLookUp = new TileLookUp();
	//GameManager * gameManager = new GameManager(tileLookUp, playerCount, playerNames);
	//gameManager->simulateGame();
	system("pause");
	return 0;
}