#include "PreEndGameManager.h"



PreEndGameManager::PreEndGameManager()
{
}


PreEndGameManager::~PreEndGameManager()
{
}

Move PreEndGameManager::GenerateMove()
{
	return Move();
}

void  PreEndGameManager::Blocking(Move  movesList[], Rack* Rack, Board b, ProbabilityManager *pm)
{
	string letters = b.getBoardLetters();
	char* boardpool = new char[letters.length() + 1];
	strcpy(boardpool, letters.c_str());
	int size = sizeof(movesList) / sizeof(Move);
	MonteCarlo * M = new MonteCarlo(Rack, boardpool, pm);
	vector<pair<vector<char>, double>> estimatedRackCost = M->simulation();
	for (int i = 0; i < size; i++ ) 
	{		
		double costestimated = 0;
		double weightestimated = 0;
		int futureWeight=(double)this->Heu->preEnd( movesList[i], Rack);
		Board * B =  b.commitMoveSim(movesList[i]);
		MoveGenerator * MG = new MoveGenerator();
		for (auto rack = estimatedRackCost.begin(); rack != estimatedRackCost.end(); rack++)
		{
			double Costweighted = 0.0f;
			double max = 0.0f;
			double weightes = 0.0f;
			vector<Move> M = 	MG->generateMoves((*rack).first, B);
			for (auto move = M.begin(); move != M.end(); move++) {
					max = (max > scoreManager->computeMoveScore(*move,&B))? max: 
			}
		}
	}
		
	}


Move * PreEndGameManager::Fishing()
{
	return nullptr;
}

Move * PreEndGameManager::
GoodEndGame()
{
	return nullptr;
}
