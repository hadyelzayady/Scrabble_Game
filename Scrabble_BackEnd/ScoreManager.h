#pragma once
#include "Board.h"
#include "TileLookUp.h"
#include <cmath>
class ScoreManager
{
  public:
	// Parameters
	Board *boardManager;
	TileLookUp *tileLookUp;

	// Methods
	double computeMoveScore(Move M, Board *B);
	ScoreManager(Board *, TileLookUp *);
	~ScoreManager();
};
