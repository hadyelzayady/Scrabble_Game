#include "PreEndGameManager.h"



PreEndGameManager::PreEndGameManager( TileLookUp * Tp, Gaddag * GD)
{
	this->Heu = new Heuristics();
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

Move  PreEndGameManager::Blocking(vector<Move>  movesList, Rack* Rack, Board b, ProbabilityManager *pm)
{
	string letters = b.getBoardLetters();
	char* boardpool = new char[letters.length()];	
	strcpy_s(boardpool,sizeof(boardpool), letters.c_str());
	int size = movesList.size();
//	cout <<"move list size"<<movesList.size() << endl;
	MonteCarlo * M = new MonteCarlo(Rack, boardpool, pm);
	vector<pair<vector<char>, double>> estimatedRackCost;
	estimatedRackCost.reserve(100);
	estimatedRackCost = M->simulation(100); //nehwal ne reserve
	Move *BestMove = NULL;
	long double BestScore = 0;
	long double EstimatedScore = 0;


	vector<pair<Move, double>> blockingCosts;
	blockingCosts.reserve(size);
	size = (size < 100) ? size : 100;
	for (int i = 0; i < size; i++)
	{
		long	double costestimated = 0;
		long double weightestimated = 0;

		//MY SCORE 
		long double myScore = ScoreManager::calculateScore(movesList[i], &b,this->TP);

		// Future
		long double futureScore = (double)this->Heu->preEnd(movesList[i], Rack->getLeave(movesList[i]), Rack->getUniqueLeave(movesList[i]));
		Board B = Board::commitMoveSim(movesList[i], b);
		B.computeCrossSets(MG->root);
		long double weightedAverageOpponentScore = 0;
		long double Weights = 0;
		long double fishingFuture = 0.0f;
		vector<char> rackleave;
		rackleave.reserve(7);
		rackleave = Rack->getLeave(movesList[i]);
		for (int rackIndex = 0; rackIndex < estimatedRackCost.size(); rackIndex++)
		{
			pair<vector<char>, double>rack = estimatedRackCost[rackIndex];
			long double Costweighted = 0.0f;
			// Max Opponent Score
			long double fishingscore = 0.0f;
			long double max = 0.0f;
			long double weightes = 0.0f;
			//thread 
			vector<Move> MovesGenerated;
			this->MG->findWords((rack).first, MovesGenerated, &B); //1sec
		int MoveGenSize = (MovesGenerated.size() > 100) ? MovesGenerated.size() : MovesGenerated.size();
			for (int moveindex = 0; moveindex < MoveGenSize; moveindex++) {  // loop khale be el index 
				//todo changed with Rackleave
				//ha thread we call 
				fishingscore +=   Fishing((MovesGenerated[moveindex]), B, rackleave, this->MG, this->TP);
				//ha join 

				long double scoreMax = ScoreManager::calculateScore(MovesGenerated[moveindex], &B, this->TP);
				max = (max > (scoreMax)) ? max : scoreMax;
			}
			fishingscore /= MovesGenerated.size();
			fishingFuture += fishingscore;
			long double maxcost = (rack).second * max;
			weightedAverageOpponentScore += maxcost;
			weightes += (rack).second;
		}
		//	Opponent Score
		weightedAverageOpponentScore /=-log10(Weights);
		fishingFuture /= estimatedRackCost.size();
		EstimatedScore = myScore - weightedAverageOpponentScore + futureScore + fishingFuture;
		if (BestScore < EstimatedScore) {
			BestScore = EstimatedScore;
			BestMove = &movesList[i];
		}
				//blockingCosts.push_back(make_pair(movesList[i], EstimatedScore));
	}
	return *BestMove;

}
 double   PreEndGameManager::Fishing( const Move &move,const Board & B,const vector<char> &RackLeave, Gaddag* MG, TileLookUp* Tup)
{
	 
	Board newBoard = Board::commitMoveSim(move, B);
	vector<Move> moveList;
	MG->findWords(RackLeave, moveList, &newBoard);
	double maxScorePerMove = 0.0f;
	int sizeMoveList = moveList.size();
	sizeMoveList = (sizeMoveList > 10) ? 10 : sizeMoveList;
	for (int i = 0; i < sizeMoveList; i++) {   //eb2a zabtha le el Size !!!
		double score = ScoreManager::calculateScore(moveList[i], &newBoard, Tup);
		maxScorePerMove = (maxScorePerMove < score) ? score : maxScorePerMove;

	}
	return  maxScorePerMove;
}




Move * PreEndGameManager::GoodEndGame()
{
	return NULL;
}
