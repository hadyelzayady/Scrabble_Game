#pragma once
#include "Square.h"
#include "Rack.h"
#include "ScoreManager.h"
class EndSimulation
{
	ScoreManager *scoreManager;

public:
	EndSimulation(Square board[ROWS_COUNT][COLUMNS_COUNT]);
	Rack opponetRack;
	Rack myRack;
	int minimax(Board board, int score, int alpha, int beta, bool maximizingPlayer);
	void start();
	EndSimulation(ScoreManager *scoreManager);
	~EndSimulation();
};
