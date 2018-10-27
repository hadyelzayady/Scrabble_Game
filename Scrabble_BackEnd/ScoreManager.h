#pragma once
#include "Board.h"
#include "TileLookUp.h"
#include <cmath>
class ScoreManager
{
public:
	// Parameters
	Board * boardManager;
	TileLookUp * tileLookUp;

	// Methods
	int computeMoveScore(int[],int[],char[],int);
	ScoreManager(Board*, TileLookUp*);
	~ScoreManager();
};

