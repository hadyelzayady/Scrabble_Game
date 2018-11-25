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

Move * PreEndGameManager::Blocking(Move  movesList[] ,Rack Rack , Board  board, ProbabilityManager *pm)
{
	int size = sizeof(movesList) / sizeof(Move);
	vector<double> Costs;
	for (int i = 0; i < size; i++ ) 
	{
		Board b =  board.move(movesList[i]);
		 char* boardpool = b.getboardpool();
		 MonteCarlo * M = new MonteCarlo(Rack, boardpool, pm);
		double cost= M->simulation(); // simulation gowha handi 3ala compute board cost fe halet kol move hanshof eh ahsan move we cost bet3ha howa momken el3bha hatdelo ad eh bensbla lel simulated rack
		costs.push_back(cost);
	
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
