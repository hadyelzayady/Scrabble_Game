#pragma once
#include "Square.h"
#include "Rack.h"
#include "ScoreManager.h"
class EndSimulation
{
	ScoreManager *scoreManager;

public:
	Rack opponetRack;
	Rack myRack;
	Board board;
	int minimax(Board board, int score, int alpha, int beta, bool maximizingPlayer);
	void start();
	EndSimulation(const Board&board,ScoreManager *scoreManager, Rack opponentRack, Rack myRack);
	~EndSimulation();
};
