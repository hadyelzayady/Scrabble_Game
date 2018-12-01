#include "PreEndGameManager.h"



PreEndGameManager::PreEndGameManager( TileLookUp * Tp, Gaddag * GD)
{
	this->MG = GD;
	this->TP = Tp;
}


PreEndGameManager::~PreEndGameManager()
{
}

Move PreEndGameManager::GenerateMove()
{
	return Move();
}

Move  PreEndGameManager::Blocking(Move  movesList[], Rack* Rack, Board b, ProbabilityManager *pm)
{
	string letters = b.getBoardLetters();
	char* boardpool = new char[letters.length()];	
	strcpy_s(boardpool,sizeof(boardpool), letters.c_str());
	int size = sizeof(movesList) / sizeof(Move);
	MonteCarlo * M = new MonteCarlo(Rack, boardpool, pm);
	vector<pair<vector<char>, double>> estimatedRackCost;
	estimatedRackCost.reserve(100);
	estimatedRackCost = M->simulation(); //nehwal ne reserve
	Move BestMove;
	double BestScore = 0;
	double EstimatedScore = 0;


	vector<pair<Move, double>> blockingCosts;
	blockingCosts.reserve(size);
	for (int i = 0; i < size; i++)
	{
		double costestimated = 0;
		double weightestimated = 0;

		//MY SCORE 
		double myScore = ScoreManager::calculateScore(movesList[i], b,this->TP);

		// Future
		double futureScore = (double)this->Heu->preEnd(movesList[i], Rack->getLeave(movesList[i]), Rack->getUniqueLeave(movesList[i]));
		Board B = Board::commitMoveSim(movesList[i], b);
		double weightedAverageOpponentScore = 0;
		double Weights = 0;
		double fishingFuture = 0.0f;
		for (int rackIndex = 0; rackIndex < estimatedRackCost.size(); rackIndex++)
		{
			pair<vector<char>, double>rack = estimatedRackCost[rackIndex];
			double Costweighted = 0.0f;
			// Max Opponent Score
			double fishingscore = 0.0f;
			double max = 0.0f;
			double weightes = 0.0f;
			//thread 
		vector<Move> M = this->MG->findWords((rack).first, B); //1sec
		
			for (int moveindex = 0; moveindex < M.size(); moveindex++) {  // loop khale be el index 
				//todo changed with Rackleave
				vector<char> rackleave;
				rackleave.reserve(7);
				rackleave = Rack->getLeave(M[moveindex]);
				//ha thread we call 
				fishingscore += Fishing((M[moveindex]), B, rackleave,this->MG,this->TP);
				//ha join 

				double scoreMax = ScoreManager::calculateScore(M[moveindex], B, this->TP);
				max = (max > (scoreMax)) ? max : scoreMax;
			}
			fishingscore /= M.size();
			fishingFuture += fishingscore;
			double maxcost = (rack).second * max;
			weightedAverageOpponentScore += maxcost;
			weightes += (rack).second;
		}
		//	Opponent Score
		weightedAverageOpponentScore /= Weights;
		fishingFuture /= estimatedRackCost.size();
		EstimatedScore = myScore - weightedAverageOpponentScore + futureScore + fishingFuture;
		BestMove = (BestScore >= EstimatedScore)? BestMove: movesList[i];
		blockingCosts.push_back(make_pair(movesList[i], EstimatedScore));
	}
	return BestMove;

}


Move * PreEndGameManager::GoodEndGame()
{
	return NULL;
}
